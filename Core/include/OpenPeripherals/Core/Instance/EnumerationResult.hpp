#pragma once

#include "OpenPeripherals/Core/PeripheralGraph.hpp"
#include "OpenPeripherals/Core/PhysicalPeripheral.hpp"
#include <vector>
namespace OpenPeripherals {

struct EnumerationResult {
    std::vector<PhysicalPeripheral> peripherals;
    Graph::PeripheralGraph graph;
    bool timedOut{false};
};


} // namespace OpenPeripherals
