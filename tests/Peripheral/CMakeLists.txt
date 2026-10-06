add_executable(openperipheral-peripheral-tests PeripheralTests.cpp.cpp)
find_package(GTest REQUIRED)
target_link_libraries(openperipheral-peripheral-tests PRIVATE
    OpenPeripherals::OpenPeripheral
    GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(openperipheral-peripheral-tests)
