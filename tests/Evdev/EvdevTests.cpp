


#include "OpenPeripherals/Evdev/EvdevDiscovery.hpp"
#include <gtest/gtest.h>
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(EvdevTests, EnumerateEndpoints) {
   OpenPeripherals::EvdevDiscovery discovery;
   auto endpoints = discovery.Discover();
}