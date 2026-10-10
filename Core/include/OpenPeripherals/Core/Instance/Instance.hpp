#pragma once
#include "OpenPeripherals/Core/Instance/EnumerationResult.hpp"
#include <OpenPeripherals/Core/LogicalPeripheral.hpp>
#include <OpenPeripherals/Core/Structs.hpp>

#include <memory>
#include <mutex>
#include <vector>
#include "OpenPeripherals/Core/Discovery/IDiscovery.hpp"
namespace OpenPeripherals {

class Instance {
public:
  Instance() = default;
  explicit Instance(const InstanceCreateInfo &createInfo) { (void)createInfo; }

  void RegisterDiscover(std::shared_ptr<IDiscovery> discovery);

  [[nodiscard]] EnumerationResult EnumerateDevices() const;

  std::shared_ptr<ILogicalPeripheral>
  CreateDevice(const LogicalPeripheralCreateInfo &) {
    return nullptr;
  }

private:
  mutable std::mutex providers_mutex_;
  std::vector<std::shared_ptr<IDiscovery>> providers_;
};

inline std::unique_ptr<Instance>
CreateInstance(const InstanceCreateInfo &createInfo) {
  return std::make_unique<Instance>(createInfo);
}
} // namespace OpenPeripherals
