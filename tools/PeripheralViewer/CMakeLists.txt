add_executable(OpenPeripheralsViewer src/Main.cpp)

find_package(imgui REQUIRED)
find_package(implot)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(OpenPeripheralsViewer PRIVATE
OpenPeripherals::OpenPeripherals
OpenPeripherals::EvDev::Discovery

    imgui::imgui
    glfw
    OpenGL::GL
    implot::implot)
