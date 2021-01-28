cmake_minimum_required(VERSION 3.17)
project(Sirius)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY bin/${CMAKE_BUILD_TYPE}/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

include_directories(include)
include_directories(vendor/GLFW/include/)

### LIBRARY ###
add_library(Sirius SHARED include/Sirius/EntryPoint.h src/Sirius/Simulation.cpp include/Sirius/Simulation.h include/Sirius.h include/srspch.h include/Sirius/Events/Event.h include/Sirius/Events/KeyEvent.h include/Sirius/Events/ApplicationEvent.h include/Sirius/Events/MouseEvent.h include/Sirius/Window.h src/Sirius/WindowsWindow.cpp include/Sirius/WindowsWindow.h include/Sirius/Utilities/Vector2.tpp include/Sirius/Utilities/Vector2.h)

find_package(OpenGL REQUIRED)
set(CMAKE_PREFIX_PATH vendor/GLFW/lib/cmake/glfw3/)
find_package(glfw3 CONFIG)
target_link_libraries(Sirius PUBLIC opengl32 glfw)

add_custom_command(
        TARGET Sirius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/vendor/GLFW/bin/
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

target_precompile_headers(Sirius PUBLIC include/srspch.h)

### TEST EXECUTABLE ###
add_executable(Sirius_test test/Test.cpp)
target_link_libraries(Sirius_test Sirius)
