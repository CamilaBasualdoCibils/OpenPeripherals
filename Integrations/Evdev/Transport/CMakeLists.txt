find_package(boost_describe CONFIG QUIET)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)

add_library(OpenPeripheralsEvDevTransport src/EvdevTransport.cpp)
add_library(OpenPeripherals::EvDev::Transport ALIAS OpenPeripheralsEvDevTransport)

target_compile_features(OpenPeripheralsEvDevTransport PUBLIC cxx_std_23)
target_link_libraries(OpenPeripheralsEvDevTransport
    PUBLIC
    OpenPeripherals::Core
    OpenPeripherals::EvDev::Core
    PkgConfig::LIBEVDEV
    Boost::describe)

target_include_directories(OpenPeripheralsEvDevTransport
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
