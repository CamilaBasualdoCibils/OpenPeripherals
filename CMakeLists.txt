cmake_minimum_required(VERSION 3.23)

project(OpenPeripherals
    VERSION 0.1.0
    DESCRIPTION "Hardware capability and peripheral abstraction layer"
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(OPENPERIPHERAL_BUILD_TESTS "Build OpenPeripheral tests" ON)
option(OPENPERIPHERAL_BUILD_TOOLS "Build OpenPeripheral tools" ON)
option(OPENPERIPHERAL_BUILD_EXAMPLES "Build OpenPeripheral examples" ON)

add_subdirectory(Core)
add_subdirectory(OpenPeripherals)

    add_subdirectory(Integrations)



if(OPENPERIPHERAL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
if(OPENPERIPHERAL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(OPENPERIPHERAL_BUILD_TOOLS)
    add_subdirectory(tools)
endif()
