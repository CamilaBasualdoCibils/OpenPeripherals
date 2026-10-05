cmake_minimum_required(VERSION 3.23)

project(OpenPeripheral
    VERSION 0.1.0
    DESCRIPTION "Hardware capability and peripheral abstraction layer"
    LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(OPENPERIPHERAL_BUILD_TESTS "Build OpenPeripheral tests" ON)
option(OPENPERIPHERAL_BUILD_EXAMPLES "Build OpenPeripheral examples" ON)

add_library(OpenPeripheral
    src/OpenPeripheral.cpp
    src/Device.cpp)
add_library(OpenPeripheral::OpenPeripheral ALIAS OpenPeripheral)

target_compile_features(OpenPeripheral PUBLIC cxx_std_20)
target_include_directories(OpenPeripheral
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(MSVC)
    target_compile_options(OpenPeripheral PRIVATE /W4 /permissive-)
else()
    target_compile_options(OpenPeripheral PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(OpenPeripheral PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME OpenPeripheral)

install(TARGETS OpenPeripheral
    EXPORT OpenPeripheralTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT OpenPeripheralTargets
    FILE OpenPeripheralTargets.cmake
    NAMESPACE OpenPeripheral::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenPeripheral)

configure_package_config_file(
    cmake/OpenPeripheralConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/OpenPeripheralConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenPeripheral)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/OpenPeripheralConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OpenPeripheralConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/OpenPeripheralConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OpenPeripheral)

if(OPENPERIPHERAL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(OPENPERIPHERAL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
