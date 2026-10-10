find_package(boost_describe CONFIG QUIET)

add_library(OpenPeripheralsEvDevDiscovery src/EvdevDiscovery.cpp)
add_library(OpenPeripherals::EvDev::Discovery ALIAS OpenPeripheralsEvDevDiscovery)

target_compile_features(OpenPeripheralsEvDevDiscovery PUBLIC cxx_std_23)
target_link_libraries(OpenPeripheralsEvDevDiscovery
    PUBLIC
    OpenPeripherals::Core
    OpenPeripherals::EvDev::Core
    Boost::describe)

target_include_directories(OpenPeripheralsEvDevDiscovery
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)   
