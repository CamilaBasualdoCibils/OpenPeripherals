#pragma once

#include "OpenPeripheral/Device.hpp"

#include <memory>
#include <vector>

namespace OpenPeripheral {

class IProvider {
public:
    virtual ~IProvider() = default;

    [[nodiscard]] virtual std::vector<std::shared_ptr<IDevice>> EnumerateDevices() = 0;
};

} // namespace OpenPeripheral
