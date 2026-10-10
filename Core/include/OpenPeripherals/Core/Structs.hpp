#pragma once

#include <OpenPeripherals/Core/PhysicalPeripheral.hpp>
namespace OpenPeripherals {
struct InstanceCreateInfo {};
struct LogicalPeripheralCreateInfo {
    PhysicalPeripheral* physicalPeripheral;
};
} // namespace OpenPeripherals