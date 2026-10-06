#pragma once

#include "OpenPeripheral/Provider.hpp"

namespace OpenPeripherals {

// Discovers keyboard and mouse event devices exposed by Linux evdev.
// On platforms without evdev, EnumerateDevices returns an empty list.
class EvdevProvider final : public IProvider {
public:
  [[nodiscard("")]] ProviderInfo GetProviderInfo() const override {
    return ProviderInfo{"EvdevProvider", "Discovers keyboard and mouse event devices exposed by Linux evdev."};
  }

    [[nodiscard]] std::vector<std::shared_ptr<IPhysicalPeripheral>> EnumerateDevices() override;
};

} // namespace OpenPeripherals
