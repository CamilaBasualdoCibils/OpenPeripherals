#pragma once

#include "OpenPeripherals/Core/PhysicalPeripheral.hpp"
#include "OpenPeripherals/Evdev/EvdevDeviceInfo.hpp"
#include "OpenPeripherals/Evdev/EvdevQuery.hpp"
namespace OpenPeripherals::Evdev
{

class EvdevDevice final : public OpenPeripherals::PhysicalPeripheral {
public:
  explicit EvdevDevice(EvdevDeviceInfo evdevInfo,
                       Evdev::DeviceCapabilities capabilities, DeviceInfo info)
      : evdevInfo_(std::move(evdevInfo)),
        capabilities_(std::move(capabilities)), info_(std::move(info)) {}

  [[nodiscard]] const DeviceInfo &GetInfo() const noexcept override {
    return info_;
  }

  [[nodiscard]] const EvdevDeviceInfo& GetEvdevInfo() const noexcept {
    return evdevInfo_;
  }
  [[nodiscard]] const Evdev::DeviceCapabilities& GetEvdevCapabilities() const noexcept {
    return capabilities_;
  }
  [[nodiscard]] std::span<const StateDescriptor> GetStates() const override {
    return {};
  }

  [[nodiscard]] std::span<const EventDescriptor> GetEvents() const override {
    return {};
  }

  [[nodiscard]] std::span<const StreamDescriptor> GetStreams() const override {
    return {};
  }

  [[nodiscard]] std::span<const OperationDescriptor>
  GetOperations() const override {
    return {};
  }

  [[nodiscard]] std::span<const ResourceDescriptor>
  GetResources() const override {
    return {};
  }

private:
  EvdevDeviceInfo evdevInfo_;
  Evdev::DeviceCapabilities capabilities_;
  DeviceInfo info_;
};
};