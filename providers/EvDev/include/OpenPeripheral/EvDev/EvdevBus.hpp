#pragma once

#include <boost/describe/enum.hpp>
#ifdef __linux__
#include <linux/input.h>

#endif
namespace OpenPeripherals::Evdev {
    
enum class EvdevBus {
  PCI = BUS_PCI,
  USB = BUS_USB,
  BLUETOOTH = BUS_BLUETOOTH,
  I2C = BUS_I2C,
  SPI = BUS_SPI,
  RMI = BUS_RMI,
  CEC = BUS_CEC,
  INTEL_ISHTP = BUS_INTEL_ISHTP,
  UNKNOWN = -1
};
BOOST_DESCRIBE_ENUM(EvdevBus, PCI, USB, BLUETOOTH, I2C, SPI, RMI, CEC,
                    INTEL_ISHTP, UNKNOWN)
} // namespace OpenPeripherals::Evdev