#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace OpenPeripherals {

enum class IdentityType : std::uint8_t {
  OpenPeripherals,
  USB,
  Bluetooth,
  System,
  Custom
};

struct IdentityClaim {
  IdentityType type;
  std::string value;
};

struct PeripheralIdentity {
  std::vector<IdentityClaim> claims;
};
} // namespace OpenPeripherals