#pragma once

#include "OpenPeripherals/Core/Discovery/Endpoint.hpp"
#include "OpenPeripherals/Core/Discovery/PeripheralIdentity.hpp"
#include "OpenPeripherals/Core/Discovery/PeripheralInfo.hpp"
namespace OpenPeripherals {
struct PeripheralObservation {
  PeripheralIdentity identity;
  PeripheralInfo info;
  Endpoint endpoint;
};
} // namespace OpenPeripherals