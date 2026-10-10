#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
namespace OpenPeripherals {

struct PeripheralExtension {
  std::string name;
  uint32_t version{1};
};
inline constexpr std::string_view OP_PERIPHERAL_DISPLAY_EXTENSION_NAME =
    "OP_PERIPHERAL_DISPLAY_EXTENSION";
struct OPPeripheralDisplayProperties {
  uint32_t width;
  uint32_t height;
  float refreshRate;
  bool supportsHDR;
};

inline constexpr std::string_view OP_PERIPHERAL_NETWORK_ACCESS_EXTENSION_NAME =
    "OP_PERIPHERAL_NETWORK_ACCESS_EXTENSION";

} // namespace OpenPeripherals