#pragma once
#include "OpenPeripherals/Core/PhysicalPeripheral.hpp"
#include <vector>

namespace OpenPeripherals
{
class IConnection {
public:
    virtual ~IConnection() = default;

    [[nodiscard]]
    virtual bool IsConnected() const noexcept = 0;

/*     virtual StateValue GetState(StateID id) = 0;

    virtual void SetState(
        StateID id,
        const StateValue& value) = 0;

    virtual SubscriptionID Subscribe(
        StreamID id,
        StreamCallback callback) = 0;

    virtual void Invoke(
        OperationID id,
        const OperationArguments& args) = 0; */

    virtual void Close() = 0;
};
}
