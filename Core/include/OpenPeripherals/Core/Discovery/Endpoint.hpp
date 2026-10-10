#pragma once
#include "OpenPeripherals/Core/Types.hpp"
#include "OpenPeripherals/Core/UUID.hpp"
namespace OpenPeripherals {
using EndpointID = UUID;

#include <string>
#include <optional>

struct Endpoint {
    EndpointID id;

    std::string connectionType;
    std::string address;

    // Optional identity hint, not necessarily verified.
    std::optional<PeripheralID> peripheralHint;
};

} // namespace OpenPeripherals