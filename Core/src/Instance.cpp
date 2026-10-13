#include "OpenPeripherals/Core/Instance/Instance.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>

namespace OpenPeripherals {
namespace {

std::string IdentityKey(const PeripheralIdentity &identity,
                        const Endpoint &endpoint) {
  std::vector<std::string> claims;
  claims.reserve(identity.claims.size());
  for (const auto &claim : identity.claims) {
    claims.push_back(std::to_string(static_cast<unsigned int>(claim.type)) +
                     ":" + std::to_string(claim.value.size()) + ":" +
                     claim.value);
  }
  std::sort(claims.begin(), claims.end());

  std::string key;
  for (const auto &claim : claims) {
    key += claim;
    key.push_back('|');
  }
  if (key.empty()) {
    key = "endpoint:" + endpoint.id.to_string();
  }
  return key;
}

PeripheralID MakeStableId(const std::string &key) {
  auto hash = [&key](std::uint64_t seed) {
    std::uint64_t result = seed;
    for (const unsigned char character : key) {
      result ^= character;
      result *= 1099511628211ULL;
    }
    return result;
  };

  std::ostringstream formatted;
  formatted << std::hex << std::setfill('0') << std::setw(16)
            << hash(14695981039346656037ULL) << std::setw(16)
            << hash(7809847782465536322ULL);
  std::string uuid = formatted.str();
  uuid.insert(20, "-");
  uuid.insert(16, "-");
  uuid.insert(12, "-");
  uuid.insert(8, "-");
  return PeripheralID::from_string(uuid);
}

std::string EndpointKey(const Endpoint &endpoint) {
  return endpoint.id.to_string() + "|" + endpoint.connectionType + "|" +
         endpoint.address;
}

std::string LocalMachineId() {
  std::ifstream machineIdFile("/etc/machine-id");
  std::string machineId;
  if (machineIdFile >> machineId)
    return machineId;

  char hostname[256]{};
  if (gethostname(hostname, sizeof(hostname) - 1) == 0 && hostname[0] != '\0')
    return hostname;
  return "local-machine";
}

} // namespace

void Instance::RegisterDiscover(std::shared_ptr<IDiscovery> discovery) {
  if (!discovery) {
    throw std::invalid_argument("Discovery provider must not be null");
  }

  std::scoped_lock lock(providers_mutex_);
  providers_.push_back(std::move(discovery));
}

EnumerationResult Instance::EnumeratePeripherals() const {
  std::vector<std::shared_ptr<IDiscovery>> providers;
  {
    std::scoped_lock lock(providers_mutex_);
    providers = providers_;
  }

  std::vector<PeripheralObservation> observations;
  for (const auto &provider : providers) {
    if (!provider) {
      continue;
    }
    auto found = provider->Discover();
    observations.insert(observations.end(),
                        std::make_move_iterator(found.begin()),
                        std::make_move_iterator(found.end()));
  }

  EnumerationResult result;
  std::unordered_map<PeripheralID, std::size_t> peripheralIndices;
  std::unordered_set<std::string> seenEndpoints;
  const PeripheralID machineId = MakeStableId("machine:" + LocalMachineId());

  for (auto &observation : observations) {
    const std::string key = IdentityKey(observation.identity, observation.endpoint);
    const PeripheralID id = observation.endpoint.peripheralHint.value_or(
        MakeStableId(key));

    auto [it, inserted] = peripheralIndices.try_emplace(id, result.peripherals.size());
    if (inserted) {
      result.peripherals.push_back(PhysicalPeripheral{
          .id = id,
          .identity = std::move(observation.identity),
          .info = std::move(observation.info),
      });
    } else {
      auto &existing = result.peripherals[it->second];
      // Providers can observe the same physical device. Keep the first
      // populated descriptive fields and merge additional identity claims.
      for (auto &claim : observation.identity.claims) {
        const auto duplicate = std::find_if(
            existing.identity.claims.begin(), existing.identity.claims.end(),
            [&claim](const IdentityClaim &current) {
              return current.type == claim.type && current.value == claim.value;
            });
        if (duplicate == existing.identity.claims.end()) {
          existing.identity.claims.push_back(std::move(claim));
        }
      }
      if (existing.info.name.empty())
        existing.info.name = std::move(observation.info.name);
      if (existing.info.manufacturer.empty())
        existing.info.manufacturer = std::move(observation.info.manufacturer);
      if (existing.info.model.empty())
        existing.info.model = std::move(observation.info.model);
      if (existing.info.description.empty())
        existing.info.description = std::move(observation.info.description);
      for (auto &extension : observation.info.extensions) {
        const auto duplicate = std::find_if(
            existing.info.extensions.begin(), existing.info.extensions.end(),
            [&extension](const PeripheralExtension &current) {
              return current.name == extension.name &&
                     current.version == extension.version;
            });
        if (duplicate == existing.info.extensions.end()) {
          existing.info.extensions.push_back(std::move(extension));
        }
      }
    }

    auto &peripheral = result.peripherals[it->second];
    const std::string endpointKey = EndpointKey(observation.endpoint);
    if (seenEndpoints.insert(endpointKey).second) {
      peripheral.endpoints.push_back(observation.endpoint);
    }
  }

  result.graph.AddMachine(machineId, "This machine");
  for (const auto &peripheral : result.peripherals) {
    result.graph.AddPeripheral(peripheral.id, peripheral.info.name);
  }

  Graph::EdgeID edgeId = 0;
  for (const auto &peripheral : result.peripherals) {
    if (peripheral.endpoints.empty()) {
      Endpoint localEndpoint{
          .id = MakeStableId("local-link:" + peripheral.id.to_string()),
          .connectionType = "local",
          .address = peripheral.id.to_string(),
          .peripheralHint = peripheral.id,
      };
      result.graph.AddConnection(machineId, peripheral.id, edgeId++,
                                 std::move(localEndpoint));
      continue;
    }

    for (const auto &endpoint : peripheral.endpoints) {
      result.graph.AddConnection(machineId, peripheral.id, edgeId++, endpoint);
    }
  }

  for (const auto &peripheral : result.peripherals) {
    for (const auto &endpoint : peripheral.endpoints) {
      if (!endpoint.peripheralHint || *endpoint.peripheralHint == peripheral.id ||
          !peripheralIndices.contains(*endpoint.peripheralHint)) {
        continue;
      }
      result.graph.AddConnection(peripheral.id, *endpoint.peripheralHint,
                                 edgeId++, endpoint);
    }
  }

  return result;
}

} // namespace OpenPeripherals
