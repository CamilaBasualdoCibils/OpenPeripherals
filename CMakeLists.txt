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

find_package(boost_describe CONFIG REQUIRED)


add_library(OpenPeripherals
    src/OpenPeripheral.cpp)
add_library(OpenPeripherals::OpenPeripherals ALIAS OpenPeripherals)

target_include_directories(OpenPeripherals
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(OpenPeripherals
    PUBLIC
        Boost::describe)

set_target_properties(OpenPeripherals PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME OpenPeripherals)


if(OPENPERIPHERAL_BUILD_TESTS)
    enable_testing()
    #add_subdirectory(tests)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(providers/EvDev)
endif()
if(OPENPERIPHERAL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(OPENPERIPHERAL_BUILD_TOOLS)
    add_subdirectory(tools)
endif()
