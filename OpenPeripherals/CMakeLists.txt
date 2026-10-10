add_library(OpenPeripherals
    src/OpenPeripherals.cpp)
add_library(OpenPeripherals::OpenPeripherals ALIAS OpenPeripherals)

target_compile_features(OpenPeripherals PUBLIC cxx_std_23)
target_include_directories(OpenPeripherals
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(OpenPeripherals PUBLIC OpenPeripherals::Core)

set_target_properties(OpenPeripherals PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME OpenPeripherals)
