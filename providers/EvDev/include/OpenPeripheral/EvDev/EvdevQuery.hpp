#pragma once
#include "OpenPeripheral/EvDev/EvdevCodes.hpp"
#include <array>
#include <boost/describe.hpp>
#include <boost/describe/enum.hpp>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <libevdev/libevdev.h>
#include <linux/input.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
namespace OpenPeripherals::Evdev {

constexpr std::size_t BitsPerWord = sizeof(unsigned long) * 8;

constexpr std::size_t WordCount(std::size_t maxBit) {
  return (maxBit + BitsPerWord) / BitsPerWord;
}

constexpr bool TestBit(const unsigned long *bits, unsigned int bit) {
  return (bits[bit / BitsPerWord] & (1UL << (bit % BitsPerWord))) != 0;
}

// ---------------------------------------------------------------------------
// Raw component representation
// ---------------------------------------------------------------------------

struct AbsoluteInfo {
  int value{};
  int minimum{};
  int maximum{};
  int fuzz{};
  int flat{};
  int resolution{};
};
enum class EvDevTypes {
  Syn = EV_SYN,
  Key = EV_KEY,
  Relative = EV_REL,
  Absolute = EV_ABS,
  Led = EV_LED,
  Switch = EV_SW,
  Sound = EV_SND,
  Repeat = EV_REP,
  ForceFeedback = EV_FF,
  Power = EV_PWR,
  ForceFeedbackStatus = EV_FF_STATUS,
  Misc = EV_MSC
};

BOOST_DESCRIBE_ENUM(EvDevTypes, Key, Relative, Absolute, Led, Switch, Sound,
                    Repeat, ForceFeedback, Power, ForceFeedbackStatus, Misc);

struct Component {
  // EV_KEY, EV_REL, EV_ABS, EV_LED, ...
  EvDevTypes type{};

  // KEY_A, BTN_LEFT, REL_X, ABS_X, ...
  Evdev::EvDevCodes code{};

  // Only populated for EV_ABS.
  bool hasAbsoluteInfo{false};
  AbsoluteInfo absolute{};
};

struct DeviceCapabilities {
  std::unordered_map<EvDevTypes, std::vector<Component>> components;
};

// ---------------------------------------------------------------------------
// Individual event type parsers
// ---------------------------------------------------------------------------

inline void QueryKeys(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(KEY_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= KEY_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Key].push_back(Component{
        .type = EvDevTypes::Key,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

inline void QueryRelativeAxes(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(REL_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_REL, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= REL_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Relative].push_back(Component{
        .type = EvDevTypes::Relative,
        .code = Evdev::EvDevCodes(code) ,
    });
  }
}

inline  void QueryAbsoluteAxes(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(ABS_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= ABS_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    input_absinfo absInfo{};

    const bool gotInfo = ioctl(fd, EVIOCGABS(code), &absInfo) >= 0;

    Component component{
        .type = EvDevTypes::Absolute,
        .code = Evdev::EvDevCodes(code),
    };

    if (gotInfo) {
      component.hasAbsoluteInfo = true;

      component.absolute = AbsoluteInfo{
          .value = absInfo.value,
          .minimum = absInfo.minimum,
          .maximum = absInfo.maximum,
          .fuzz = absInfo.fuzz,
          .flat = absInfo.flat,
          .resolution = absInfo.resolution,
      };
    }

    result.components[EvDevTypes::Absolute].push_back(component);
  }
}

inline  void QuerySwitches(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(SW_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_SW, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= SW_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Switch].push_back(Component{
        .type = EvDevTypes::Switch,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

inline void QueryLEDs(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(LED_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_LED, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= LED_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Led].push_back(Component{
        .type = EvDevTypes::Led,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

inline void QuerySounds(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(SND_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_SND, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= SND_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Sound].push_back(Component{
        .type = EvDevTypes::Sound,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

inline void QueryMisc(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(MSC_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_MSC, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= MSC_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::Misc].push_back(Component{
        .type = EvDevTypes::Misc,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

inline void QueryForceFeedback(int fd, DeviceCapabilities &result) {
  std::array<unsigned long, WordCount(FF_MAX)> bits{};

  if (ioctl(fd, EVIOCGBIT(EV_FF, sizeof(bits)), bits.data()) < 0) {
    return;
  }

  for (unsigned int code = 0; code <= FF_MAX; ++code) {
    if (!TestBit(bits.data(), code)) {
      continue;
    }

    result.components[EvDevTypes::ForceFeedback].push_back(Component{
        .type = EvDevTypes::ForceFeedback,
        .code = Evdev::EvDevCodes(code),
    });
  }
}

// ---------------------------------------------------------------------------
// Main capability query
// ---------------------------------------------------------------------------

inline DeviceCapabilities QueryComponents(int fd) {
  DeviceCapabilities result;

  //
  // First ask:
  //
  //     "Which EVENT TYPES does this device support?"
  //
  // This gives us EV_KEY, EV_REL, EV_ABS, etc.
  //

  std::array<unsigned long, WordCount(EV_MAX)> eventTypes{};

  if (ioctl(fd, EVIOCGBIT(0, sizeof(eventTypes)), eventTypes.data()) < 0) {
    return result;
  }

  //
  // Now query inside each supported event type.
  //

  if (TestBit(eventTypes.data(), EV_KEY)) {
    QueryKeys(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_REL)) {
    QueryRelativeAxes(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_ABS)) {
    QueryAbsoluteAxes(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_SW)) {
    QuerySwitches(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_LED)) {
    QueryLEDs(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_SND)) {
    QuerySounds(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_MSC)) {
    QueryMisc(fd, result);
  }

  if (TestBit(eventTypes.data(), EV_FF)) {
    QueryForceFeedback(fd, result);
  }

  return result;
}

} // namespace OpenPeripherals::Evdev