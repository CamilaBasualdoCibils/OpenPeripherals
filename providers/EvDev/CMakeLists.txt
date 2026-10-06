add_library(OpenPeripheralsEvDev EvdevProvider.cpp)
add_library(OpenPeripherals::EvDev ALIAS OpenPeripheralsEvDev)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)


target_compile_features(OpenPeripheralsEvDev PUBLIC cxx_std_23)
target_link_libraries(OpenPeripheralsEvDev
    PUBLIC
        OpenPeripherals::OpenPeripherals
        PkgConfig::LIBEVDEV)
target_include_directories(OpenPeripheralsEvDev
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
