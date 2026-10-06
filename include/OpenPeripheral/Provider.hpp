#pragma once



#include "OpenPeripheral/PhysicalPeripheral.hpp"
#include <memory>
#include <vector>

namespace OpenPeripherals {

struct ProviderInfo {
  std::string name;
  std::string description;
};
class IProvider {
public:
  [[nodiscard]] virtual ProviderInfo GetProviderInfo() const = 0;

public:
  virtual ~IProvider() = default;

  [[nodiscard]] virtual std::vector<std::shared_ptr<IPhysicalPeripheral>>
  EnumerateDevices() = 0;
};

} // namespace OpenPeripherals
