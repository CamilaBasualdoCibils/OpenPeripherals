#pragma once

#include <OpenPeripherals/Core/Types.hpp>
#include <OpenPeripherals/Core/Discovery/Endpoint.hpp>
#include <OpenPeripherals/Core/Discovery/PeripheralIdentity.hpp>
#include <OpenPeripherals/Core/Discovery/PeripheralInfo.hpp>
#include <optional>
#include <vector>

namespace OpenPeripherals {
struct ComponentDescriptor {
  ComponentID id;
  std::string name;
  std::string description;
};
/* struct ControlDescriptor : ComponentDescriptor {

  ValueType type; // Bool, Float, Vec2, Vec3...
  ValueRange range;
  std::vector<ComponentSemantic> semantics;
}; */
struct StateDescriptor : ComponentDescriptor {
  ValueType type;
  Access access;
  Unit unit;
};
struct FieldDescriptor {
  std::string name;
  ValueType type;
  std::string description;
};
struct EventDescriptor : ComponentDescriptor {
    std::vector<FieldDescriptor> fields;
};

struct OperationDescriptor : ComponentDescriptor {
    std::vector<FieldDescriptor> Arguments;
    std::vector<FieldDescriptor> Results;
};
struct StreamDescriptor : ComponentDescriptor {
    StreamDirection direction;
    StreamType type;

    std::optional<double> nominalRate;
};
struct ResourceDescriptor : ComponentDescriptor {
    std::string mediaType;

    std::optional<std::uint64_t> size;
};
struct PhysicalPeripheral final {
  PeripheralID id{};
  PeripheralIdentity identity;
  PeripheralInfo info;
  std::vector<Endpoint> endpoints;
  std::vector<StateDescriptor> states;
  std::vector<EventDescriptor> events;
  std::vector<StreamDescriptor> streams;
  std::vector<OperationDescriptor> operations;
  std::vector<ResourceDescriptor> resources;
};

} // namespace OpenPeripherals
