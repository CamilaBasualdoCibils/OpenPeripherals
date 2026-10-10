

add_library(OpenPeripheralsEvDevCore src/Evdev.cpp)
add_library(OpenPeripherals::EvDev::Core ALIAS OpenPeripheralsEvDevCore)

target_compile_features(OpenPeripheralsEvDevCore PUBLIC cxx_std_23)
target_link_libraries(OpenPeripheralsEvDevCore
    PUBLIC
    OpenPeripherals::Core
    )

target_include_directories(OpenPeripheralsEvDevCore
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
