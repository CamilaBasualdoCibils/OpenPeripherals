#pragma once

#include "OpenPeripheral/PhysicalPeripheral.hpp"
namespace OpenPeripherals {
struct InstanceCreateInfo {};
struct LogicalPeripheralCreateInfo {
    IPhysicalPeripheral* physicalPeripheral;
};
} // namespace OpenPeripherals