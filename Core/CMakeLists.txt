add_library(OpenPeripheralsCore STATIC src/OpenPeripherals.cpp src/Instance.cpp)
add_library(OpenPeripherals::Core ALIAS OpenPeripheralsCore)
find_package(boost_describe CONFIG QUIET)
find_package(boost_uuid CONFIG QUIET)
find_package(boost_graph CONFIG QUIET)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED IMPORTED_TARGET libevdev)


target_compile_features(OpenPeripheralsCore PUBLIC cxx_std_23)
target_include_directories(OpenPeripheralsCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

        target_link_libraries(OpenPeripheralsCore
            PUBLIC
            PkgConfig::LIBEVDEV
            Boost::describe
            Boost::uuid
            Boost::graph
        )
set_target_properties(OpenPeripheralsCore PROPERTIES EXPORT_NAME Core)
