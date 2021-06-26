
# ----------------------------------------------------
# Start Sirius project
# ----------------------------------------------------

cmake_minimum_required(VERSION 3.17)
project(Sirius VERSION 0.1)

# Bin directory #
file(MAKE_DIRECTORY bin/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# ----------------------------------------------------
# Compiler and build configuration
# ----------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# ----------------------------------------------------
# Sirius include directories and definitions
# ----------------------------------------------------

add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(include)
include_directories(vendor/spdlog/include/)
include_directories(vendor/imgui/)
include_directories(vendor/glfw/include/)
include_directories(vendor/glad/include/)
include_directories(vendor/glm)
include_directories(vendor/stb_image)

# ----------------------------------------------------
# Sirius library and dependencies
# ----------------------------------------------------

### LIBRARY ###
add_library(Sirius SHARED include/Sirius/Core/EntryPoint.h src/Sirius/Core/Application.cpp include/Sirius/Core/Application.h include/Sirius.h include/srspch.h include/Sirius/Events/Event.h include/Sirius/Events/KeyEvent.h include/Sirius/Events/ApplicationEvent.h include/Sirius/Events/MouseEvent.h include/Sirius/Core/Window.h include/Sirius/Core/Input.h src/Sirius/Core/Input.cpp src/Sirius/Core/Window.cpp src/Sirius/Renderer/Buffer.cpp include/Sirius/Renderer/Buffer.h include/Sirius/Renderer/Shader.h src/Sirius/Renderer/Shader.cpp include/Sirius/Renderer/RenderContext.h src/Sirius/Renderer/RenderContext.cpp src/Sirius/Renderer/VertexArray.cpp include/Sirius/Renderer/VertexArray.h src/Sirius/Core/Log.cpp include/Sirius/Core/Log.h include/Sirius/Core/Core.h src/Sirius/Core/Layer.cpp include/Sirius/Core/Layer.h src/Sirius/Core/LayerStack.cpp include/Sirius/Core/LayerStack.h src/Sirius/ImGui/ImGuiLayer.cpp include/Sirius/ImGui/ImGuiLayer.h vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_glfw.h vendor/imgui/backends/imgui_impl_opengl3.cpp vendor/imgui/backends/imgui_impl_opengl3.h src/Sirius/Renderer/Renderer.cpp include/Sirius/Renderer/Renderer.h src/Sirius/Renderer/RenderCommand.cpp include/Sirius/Renderer/RenderCommand.h src/Sirius/Renderer/Camera.cpp include/Sirius/Renderer/Camera.h include/Sirius/Core/KeyCodes.h include/Sirius/Core/MouseButtonCodes.h include/Sirius/Core/Timestep.h src/Sirius/Renderer/CameraController.cpp include/Sirius/Renderer/CameraController.h src/Sirius/Renderer/Texture.cpp include/Sirius/Renderer/Texture.h include/Sirius/Math/Vector/Vector2.h include/Sirius/Math/Vector/Vector3.h include/Sirius/Math/Vector/Vector4.h include/Sirius/Math/Matrix/Matrix2.h include/Sirius/Math/Matrix/Matrix3.h include/Sirius/Math/Matrix/Matrix4.h include/Sirius/Math/Matrix/Matrix.h include/Sirius/Math/Matrix/transforms.h include/Sirius/Math/Vector/transforms.h include/Sirius/Math/Matrix/functions.h include/Sirius/Math/Math.h include/Sirius/Math/Matrix/clip_space.h)

# spdlog #
set(CMAKE_PREFIX_PATH vendor/spdlog/lib/cmake/spdlog/)
find_package(spdlog CONFIG)
target_link_libraries(Sirius PUBLIC spdlog::spdlog)

# ImGui #
add_library(imgui STATIC vendor/imgui/imgui_tables.cpp vendor/imgui/imconfig.h vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui.h vendor/imgui/imgui.cpp vendor/imgui/imgui_internal.h vendor/imgui/imstb_rectpack.h vendor/imgui/imgui_widgets.cpp vendor/imgui/imstb_textedit.h vendor/imgui/imstb_truetype.h)
target_link_libraries(Sirius PUBLIC imgui)

# glfw #
find_package(OpenGL REQUIRED)
set(CMAKE_PREFIX_PATH vendor/GLFW/lib/cmake/glfw3/)
find_package(glfw3 CONFIG)
target_link_libraries(Sirius PUBLIC opengl32 glfw)

# glad #
add_library(glad STATIC vendor/glad/src/glad.c vendor/glad/include/glad/glad.h vendor/glad/include/KHR/khrplatform.h)
target_link_libraries(Sirius PUBLIC glad)

# glm #
set(CMAKE_PREFIX_PATH vendor/glm/cmake/glm/)
find_package(glm CONFIG)
target_link_libraries(Sirius PUBLIC glm::glm)

# stb_image #
add_library(stb_image STATIC vendor/stb_image/stb_image.h vendor/stb_image/stb_image.cpp)
target_link_libraries(Sirius PUBLIC stb_image)

# Copy GLFW's DLL to the bin directory (next to the
#   Sirius_test executable)
add_custom_command(
        TARGET Sirius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/vendor/glfw/bin/
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Precompiled headers
target_precompile_headers(Sirius PUBLIC include/srspch.h)

# ----------------------------------------------------
# Install Sirius and its dependencies
# ----------------------------------------------------

install(TARGETS Sirius DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY vendor DESTINATION ${CMAKE_INSTALL_PREFIX})

# ----------------------------------------------------
# Sirius test executable
# ----------------------------------------------------

add_executable(Sirius_test test/Test.cpp)
target_link_libraries(Sirius_test Sirius -static-libgcc -static-libstdc++)
