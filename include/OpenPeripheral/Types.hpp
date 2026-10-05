#pragma once

#include <cstdint>
#include <string>

namespace OpenPeripheral {

using DeviceID = std::uint64_t;

struct DeviceInfo {
    DeviceID id{};
    std::string name;
    std::string manufacturer;
    std::string description;
};

} // namespace OpenPeripheral
