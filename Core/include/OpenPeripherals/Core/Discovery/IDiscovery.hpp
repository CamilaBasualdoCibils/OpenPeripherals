#pragma once

#include "OpenPeripherals/Core/Discovery/PeripheralObservation.hpp"
#include <OpenPeripherals/Core/Discovery/Endpoint.hpp>

#include <functional>
#include <span>

namespace OpenPeripherals {

class IDiscovery {
public:
    virtual ~IDiscovery() = default;

    // Current snapshot.
    virtual std::vector<PeripheralObservation> Discover() = 0;

    // Monitor additions and removals.
    virtual void Start() = 0;
    virtual void Stop() = 0;

    virtual void SetEndpointAddedCallback(
        std::function<void(const Endpoint&)>) = 0;

    virtual void SetEndpointRemovedCallback(
        std::function<void(EndpointID)>) = 0;
};

} // namespace OpenPeripherals
