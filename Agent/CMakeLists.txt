add_executable(OpenPeripheralsAgent src/Main.cpp)
add_executable(OpenPeripherals::Agent ALIAS OpenPeripheralsAgent)

target_compile_features(OpenPeripheralsAgent PRIVATE cxx_std_23)
target_link_libraries(OpenPeripheralsAgent
    PRIVATE
        OpenPeripherals::Core
        OpenPeripherals::OpenPeripherals)
