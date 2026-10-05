#pragma once

#include "OpenPeripheral/Provider.hpp"

#include <memory>
#include <mutex>
#include <vector>

namespace OpenPeripheral {

class Context {
public:
    Context() = default;

    void RegisterProvider(std::shared_ptr<IProvider> provider);

    [[nodiscard]] std::vector<std::shared_ptr<IDevice>> EnumerateDevices() const;

private:
    mutable std::mutex providers_mutex_;
    std::vector<std::shared_ptr<IProvider>> providers_;
};

} // namespace OpenPeripheral
