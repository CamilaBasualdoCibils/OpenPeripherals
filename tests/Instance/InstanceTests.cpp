#include "OpenPeripheral/Instance.hpp"
#include "OpenPeripheral/Structs.hpp"
#include <OpenPeripheral/OpenPeripheral.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <vector>

namespace {

TEST(Instance, BasicCreate) {
    OpenPeripherals::InstanceCreateInfo createInfo;
  std::unique_ptr<OpenPeripherals::Instance> instance =
      OpenPeripherals::CreateInstance(createInfo);
}
} // namespace
