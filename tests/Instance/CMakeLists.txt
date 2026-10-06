add_executable(openperipheral-instance-tests InstanceTests.cpp.cpp)
find_package(GTest REQUIRED)
target_link_libraries(openperipheral-instance-tests PRIVATE
    OpenPeripherals::OpenPeripheral
    GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(openperipheral-instance-tests)
