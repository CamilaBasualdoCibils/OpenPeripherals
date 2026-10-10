#pragma once

#include <OpenPeripherals/Core/Types.hpp>
#include <optional>
#include <span>
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
class PhysicalPeripheral {
public:
  virtual ~PhysicalPeripheral() = default;

  [[nodiscard]] const DeviceInfo &GetInfo() const noexcept {};

/*   [[nodiscard]]
  virtual std::span<const ControlDescriptor> GetControls() const = 0;
 */
  [[nodiscard]]
  std::span<const StateDescriptor> GetStates() const{ return {}; };

  [[nodiscard]]
   std::span<const EventDescriptor> GetEvents() const { return {}; };

  [[nodiscard]]
   std::span<const StreamDescriptor> GetStreams() const { return {}; };

  [[nodiscard]]
   std::span<const OperationDescriptor> GetOperations() const { return {}; };

  [[nodiscard]]
   std::span<const ResourceDescriptor> GetResources() const { return {}; };
  // Device capability interfaces will be defined in a future revision.
};

} // namespace OpenPeripherals
