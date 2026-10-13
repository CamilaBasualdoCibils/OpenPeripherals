#include "OpenPeripherals/Evdev/EvdevDiscovery.hpp"
#include "OpenPeripherals/Core/Discovery/Endpoint.hpp"
#include "OpenPeripherals/Evdev/EvdevBus.hpp"
#include "OpenPeripherals/Evdev/EvdevQuery.hpp"
#include <algorithm>
#include <array>
#include <cerrno>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef __linux__
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace {

OpenPeripherals::UUID MakeStableUUID(const std::string &value) {
  // FNV-1a with two independent seeds gives this local identifier a stable
  // value across scans and process restarts without needing a UUID registry.
  auto hash = [&value](std::uint64_t seed) {
    std::uint64_t result = seed;
    for (const unsigned char character : value) {
      result ^= character;
      result *= 1099511628211ULL;
    }
    return result;
  };

  const std::uint64_t high = hash(14695981039346656037ULL);
  const std::uint64_t low = hash(7809847782465536322ULL);
  std::ostringstream formatted;
  formatted << std::hex << std::setfill('0') << std::setw(16) << high
            << std::setw(16) << low;
  std::string compact = formatted.str();
  compact.insert(20, "-");
  compact.insert(16, "-");
  compact.insert(12, "-");
  compact.insert(8, "-");
  return OpenPeripherals::UUID::from_string(compact);
}

std::string NormalizePhysicalPath(std::string path) {
  // EVIOCGPHYS commonly appends /inputN to a shared device path. That suffix
  // identifies one input interface, not a separate physical device.
  const std::size_t input = path.rfind("/input");
  if (input != std::string::npos && input + 6 < path.size()) {
    const bool numericSuffix = std::all_of(
        path.begin() + static_cast<std::ptrdiff_t>(input + 6), path.end(),
        [](unsigned char character) { return std::isdigit(character) != 0; });
    if (numericSuffix)
      path.erase(input);
  }
  return path;
}

std::string NormalizeDeviceName(std::string name) {
  std::transform(name.begin(), name.end(), name.begin(),
                 [](unsigned char character) {
                   return static_cast<char>(std::tolower(character));
                 });
  return name;
}

} // namespace
std::vector<OpenPeripherals::PeripheralObservation>
OpenPeripherals::EvdevDiscovery::Discover() {

  // every evdev device
  std::error_code error;

  std::filesystem::directory_iterator iterator("/dev/input", error);
  if (error) {
    return {};
  }

  std::vector<std::filesystem::path> paths;
  std::vector<OpenPeripherals::PeripheralObservation> observations;
  for (const auto &entry : iterator) {
    const auto filename = entry.path().filename().string();

    // evdev character devices are exposed as:
    //
    //   /dev/input/event0
    //   /dev/input/event1
    //   /dev/input/event2
    //   ...
    //
    // Ignore things such as /dev/input/mice and /dev/input/mouse0.
    if (filename.starts_with("event")) {
      paths.push_back(entry.path());
    }
  }

  // event10 sorts before event2 lexicographically, but deterministic
  // enumeration is still preferable for now.
  std::sort(paths.begin(), paths.end());

  for (const auto &path : paths) {
    const int fd = open(path.c_str(), O_RDONLY | O_NONBLOCK | O_CLOEXEC);

    // The device may exist but not be readable by the current user.
    if (fd < 0) {
      std::cerr << "[EvdevProvider] Cannot open " << path << ": "
                << std::strerror(errno) << '\n';
      continue;
    }

    input_id id{};

    if (ioctl(fd, EVIOCGID, &id) < 0) {
      close(fd);
      continue;
    }

    // Human-readable kernel device name.
    std::array<char, 256> name{};
    if (ioctl(fd, EVIOCGNAME(name.size()), name.data()) < 0) {
      name[0] = '\0';
    }

    // Physical topology/path reported by the input driver.
    //
    // Examples can look roughly like:
    //   usb-0000:00:14.0-3/input0
    //   isa0060/serio0/input0
    std::array<char, 256> phys{};
    if (ioctl(fd, EVIOCGPHYS(phys.size()), phys.data()) < 0) {
      phys[0] = '\0';
    }

    // Optional unique identifier supplied by the device/driver.
    //
    // Many devices do not provide this, so an empty string is normal.
    std::array<char, 256> uniq{};
    if (ioctl(fd, EVIOCGUNIQ(uniq.size()), uniq.data()) < 0) {
      uniq[0] = '\0';
    }

    const Evdev::DeviceCapabilities capabilities = Evdev::QueryComponents(fd);

    close(fd);

    const std::string deviceName =
        name[0] != '\0' ? std::string(name.data()) : path.filename().string();

    const std::string physicalPath =
        phys[0] != '\0' ? std::string(phys.data()) : std::string{};
    const std::string normalizedPhysicalPath =
        NormalizePhysicalPath(physicalPath);

    const std::string uniqueId =
        uniq[0] != '\0' ? std::string(uniq.data()) : std::string{};

    const std::string manufacturer = std::format(
        "{} vendor {}",
        boost::describe::enum_to_string(Evdev::EvdevBus(id.bustype), "Unknown"),
        std::to_string(id.vendor));

    // Prefer an explicit unique ID. Physical topology is next, with the
    // per-input-interface suffix removed so one USB device's event nodes
    // share an identity. ACPI power-button aliases have distinct topology
    // paths, so group those by their shared bus IDs and kernel device name.
    // The event path is the final fallback when the driver exposes no better
    // identity.
    std::string deviceKey;
    if (!uniqueId.empty()) {
      deviceKey = std::format("evdev:{}:{}:{}:uniq:{}", id.bustype,
                              id.vendor, id.product, uniqueId);
    } else if (id.bustype == BUS_HOST && !deviceName.empty()) {
      deviceKey = std::format("evdev:{}:{}:{}:host:{}", id.bustype,
                              id.vendor, id.product,
                              NormalizeDeviceName(deviceName));
    } else if (!normalizedPhysicalPath.empty()) {
      deviceKey = std::format("evdev:{}:{}:{}:phys:{}", id.bustype,
                              id.vendor, id.product, normalizedPhysicalPath);
    } else {
      deviceKey = std::format("evdev:{}:{}:{}:node:{}", id.bustype,
                              id.vendor, id.product, path.string());
    }
    const PeripheralID peripheralId = MakeStableUUID(deviceKey);
    const EndpointID endpointId = MakeStableUUID("endpoint:" + path.string());

    PeripheralIdentity identity;
    identity.claims.push_back(
        {IdentityType::System, deviceKey});
    if (id.bustype == BUS_USB) {
      std::ostringstream usbIdentity;
      usbIdentity << std::hex << std::setfill('0') << std::setw(4) << id.vendor
                  << ':' << std::setw(4) << id.product;
      identity.claims.push_back({IdentityType::USB, usbIdentity.str()});
    }

    PeripheralInfo info;
    info.name = deviceName;
    info.manufacturer = manufacturer;
    info.model = std::format("{:04x}:{:04x}", id.vendor, id.product);
    info.description = std::format(
        "Linux evdev device at {} ({} components)", path.string(),
        capabilities.components.size());

    Endpoint endpoint{
        .id = endpointId,
        .connectionType = "evdev",
        .address = path.string(),
        .peripheralHint = peripheralId,
    };
    observations.push_back(
        PeripheralObservation{std::move(identity), std::move(info),
                              std::move(endpoint)});
  }

  return observations;
}
