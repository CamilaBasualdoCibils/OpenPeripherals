#include "OpenPeripherals/Core/Instance/Instance.hpp"


namespace OpenPeripherals {

/* void Instance::RegisterProvider(std::shared_ptr<IProvider> provider) {
    if (!provider) {
        throw std::invalid_argument("OpenPeripheral providers must not be null");
    }

    std::scoped_lock lock(providers_mutex_);
    providers_.push_back(std::move(provider));
} */

/* std::vector<std::shared_ptr<PhysicalPeripheral>> Instance::EnumerateDevices() const {
    std::vector<std::shared_ptr<IProvider>> providers;
    {
        std::scoped_lock lock(providers_mutex_);
        providers = providers_;
    }

    std::vector<std::shared_ptr<PhysicalPeripheral>> devices;
    for (const auto& provider : providers) {
        auto discovered = provider->EnumerateDevices();
        devices.insert(devices.end(), discovered.begin(), discovered.end());
    }
    return devices;
} */
}