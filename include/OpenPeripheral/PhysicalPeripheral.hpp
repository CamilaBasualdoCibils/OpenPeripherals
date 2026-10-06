#pragma once

#include "OpenPeripheral/Types.hpp"
#include "Types.hpp"
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
class IPhysicalPeripheral {
public:
  virtual ~IPhysicalPeripheral() = default;

  [[nodiscard]] virtual const DeviceInfo &GetInfo() const noexcept = 0;

/*   [[nodiscard]]
  virtual std::span<const ControlDescriptor> GetControls() const = 0;
 */
  [[nodiscard]]
  virtual std::span<const StateDescriptor> GetStates() const = 0;

  [[nodiscard]]
  virtual std::span<const EventDescriptor> GetEvents() const = 0;

  [[nodiscard]]
  virtual std::span<const StreamDescriptor> GetStreams() const = 0;

  [[nodiscard]]
  virtual std::span<const OperationDescriptor> GetOperations() const = 0;

  [[nodiscard]]
  virtual std::span<const ResourceDescriptor> GetResources() const = 0;
  // Device capability interfaces will be defined in a future revision.
};

} // namespace OpenPeripherals
