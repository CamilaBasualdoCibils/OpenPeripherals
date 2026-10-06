add_executable(openperipheral-enumerate enumerate.cpp)
target_link_libraries(openperipheral-enumerate PRIVATE OpenPeripherals::OpenPeripherals OpenPeripherals::EvDev)

if(MSVC)
    target_compile_options(openperipheral-enumerate PRIVATE /W4 /permissive-)
else()
    target_compile_options(openperipheral-enumerate PRIVATE -Wall -Wextra -Wpedantic)
endif()
