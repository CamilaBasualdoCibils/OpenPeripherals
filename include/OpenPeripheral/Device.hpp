#pragma once

#include "OpenPeripheral/Types.hpp"

namespace OpenPeripheral {

class IDevice {
public:
    virtual ~IDevice() = default;

    [[nodiscard]] virtual const DeviceInfo& GetInfo() const noexcept = 0;

    // Device capability interfaces will be defined in a future revision.
};

} // namespace OpenPeripheral
