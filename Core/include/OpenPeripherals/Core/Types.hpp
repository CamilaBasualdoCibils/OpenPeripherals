#pragma once

#include <array>
#include <cstdint>
#include "OpenPeripherals/Core/UUID.hpp"
#include <string>
#include <variant>
#include <functional>

namespace OpenPeripherals {
using ComponentID = std::uint32_t;
using PeripheralID = UUID;
enum class ValueType { Bool, Float, Vec2, Vec3 };
using ControlValue =
    std::variant<bool, float, std::array<float, 2>, std::array<float, 3>>;

struct ValueRange {
  ControlValue min;
  ControlValue max;
};
enum class ComponentSemantic {
    PrimarySelect,
    SecondarySelect,
    Pointer,
    Navigation,
    Scroll,
    TextInput,
};
enum class Access
{
    Read,
    Write,
    ReadWrite
};
enum class Unit
{
    None,
    Meter,
    Second,
    Degree,
    Percent
};
enum class StreamDirection {
    DeviceToHost,
    HostToDevice,
    Bidirectional
};
enum class StreamType {
    Generic,

    Audio,
    Image,
    Video,

    Pose,

    Acceleration,
    AngularVelocity,

    PointCloud,

    Binary
};
struct DeviceInfo {
  PeripheralID id{};
  std::string name;
  std::string manufacturer;
  std::string description;
};

} // namespace OpenPeripherals
