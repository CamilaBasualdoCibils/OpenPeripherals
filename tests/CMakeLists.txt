add_executable(openperipheral-basic-tests basic_tests.cpp)
target_link_libraries(openperipheral-basic-tests PRIVATE OpenPeripheral::OpenPeripheral)

if(MSVC)
    target_compile_options(openperipheral-basic-tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(openperipheral-basic-tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME openperipheral-basic-tests COMMAND openperipheral-basic-tests)
