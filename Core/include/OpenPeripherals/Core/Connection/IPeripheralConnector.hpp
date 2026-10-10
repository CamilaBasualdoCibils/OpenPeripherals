#pragma once


#include "OpenPeripherals/Core/Discovery/Endpoint.hpp"
#include "OpenPeripherals/Core/Connection/IConnection.hpp"

#include <memory>

namespace OpenPeripherals {
    class IPeripheralConnector {
public:
    virtual ~IPeripheralConnector() = default;

    virtual bool Supports(const Endpoint& endpoint) const = 0;

    virtual std::unique_ptr<IConnection>
        Connect(const Endpoint& endpoint) = 0;
};
} // namespace OpenPeripherals