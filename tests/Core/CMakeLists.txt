add_executable(openperipheral-core-tests CoreTests.cpp)
find_package(GTest REQUIRED)
target_link_libraries(openperipheral-core-tests PRIVATE
    OpenPeripherals::Core
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(openperipheral-core-tests)
