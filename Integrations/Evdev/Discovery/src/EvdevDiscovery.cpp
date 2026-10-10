#include "OpenPeripherals/Evdev/EvdevDiscovery.hpp"
#include "OpenPeripherals/Core/Discovery/Endpoint.hpp"
#include "OpenPeripherals/Evdev/EvdevBus.hpp"
#include "OpenPeripherals/Evdev/EvdevQuery.hpp"
#include <filesystem>

#ifdef __linux__
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif
std::vector<OpenPeripherals::PeripheralObservation>
OpenPeripherals::EvdevDiscovery::Discover() {

  // every evdev device
  std::error_code error;

  std::filesystem::directory_iterator iterator("/dev/input", error);
  if (error) {
    return {};
  }

  std::vector<std::filesystem::path> paths;
  std::vector<OpenPeripherals::Endpoint> endpoints;
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

    const std::string uniqueId =
        uniq[0] != '\0' ? std::string(uniq.data()) : std::string{};

    const std::string manufacturer = std::format(
        "{} vendor {}",
        boost::describe::enum_to_string(Evdev::EvdevBus(id.bustype), "Unknown"),
        std::to_string(id.vendor));

    std::cout << "Found evdev device: " << deviceName << " at " << path << '\n';
    std::cout << "  Manufacturer: " << manufacturer << '\n';
    std::cout << "  Physical path: " << physicalPath << '\n';
    std::cout << "  Unique ID: " << uniqueId << '\n';
    std::cout << "  ComponentCount: "
              << static_cast<int>(capabilities.components.size()) << '\n';

    /* DeviceInfo opInfo{HashDevice(path.string(), id), deviceName,
    manufacturer, DescribeDevice(path, id, physicalPath, uniqueId)};
    Evdev::EvdevDeviceInfo evdevInfo{.bus = Evdev::EvdevBus(id.bustype)};

    Evdev::EvdevDevice device{evdevInfo, capabilities, opInfo};
    devices.push_back(std::make_shared<Evdev::EvdevDevice>(device)); */
  }
}
