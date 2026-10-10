#pragma once

#include "OpenPeripherals/Core/PeripheralExtensions.hpp"
#include <vector>
#include <string>
namespace OpenPeripherals {
    struct PeripheralInfo {
    std::string name;
    std::string manufacturer;
    std::string model;
    std::string description;

    std::vector<PeripheralExtension> extensions;
};
}