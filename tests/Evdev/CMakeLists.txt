add_executable(openperipheral-evdev-tests EvdevTests.cpp)
find_package(GTest REQUIRED)
target_link_libraries(openperipheral-evdev-tests PRIVATE
    OpenPeripherals::EvDev::Core
    OpenPeripherals::EvDev::Discovery
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(openperipheral-evdev-tests)
