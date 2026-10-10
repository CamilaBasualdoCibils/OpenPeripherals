add_library(OpenPeripheralsLibrary src/OpenPeripheral.cpp)
add_library(OpenPeripherals::OpenPeripherals ALIAS OpenPeripheralsLibrary)

target_compile_features(OpenPeripheralsLibrary PUBLIC cxx_std_23)
target_include_directories(OpenPeripheralsLibrary
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(OpenPeripheralsLibrary PUBLIC OpenPeripherals::Core)

set_target_properties(OpenPeripheralsLibrary PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME OpenPeripherals)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(providers/EvDev)
endif()
