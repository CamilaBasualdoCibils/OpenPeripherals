#pragma once
#include "OpenPeripheral/LogicalPeripheral.hpp"
#include "OpenPeripheral/Provider.hpp"
#include "OpenPeripheral/Structs.hpp"

#include <memory>
#include <mutex>
#include <vector>

namespace OpenPeripherals {


class Instance {
public:
  Instance() = default;
  explicit Instance(const InstanceCreateInfo &createInfo) { (void)createInfo; }

  void RegisterProvider(std::shared_ptr<IProvider> provider);

  [[nodiscard]] std::vector<std::shared_ptr<IPhysicalPeripheral>> EnumerateDevices() const;

  std::shared_ptr<ILogicalPeripheral> CreateDevice(const LogicalPeripheralCreateInfo&) {
    return nullptr;
  }

private:
  mutable std::mutex providers_mutex_;
  std::vector<std::shared_ptr<IProvider>> providers_;
};

inline std::unique_ptr<Instance>
CreateInstance(const InstanceCreateInfo &createInfo) {
  return std::make_unique<Instance>(createInfo);
}
} // namespace OpenPeripherals
