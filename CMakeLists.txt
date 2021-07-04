
# ----------------------------------------------------
# Start Sirius project
# ----------------------------------------------------

cmake_minimum_required(VERSION 3.17)
project(Sirius VERSION 0.1.0)

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
# Sirius library and dependencies
# ----------------------------------------------------

### LIBRARY ###
add_library(Sirius SHARED include/Sirius/Core/EntryPoint.hpp src/Sirius/Core/Application.cpp include/Sirius/Core/Application.hpp include/Sirius.hpp include/srspch.hpp include/Sirius/Events/Event.hpp include/Sirius/Events/KeyEvent.hpp include/Sirius/Events/ApplicationEvent.hpp include/Sirius/Events/MouseEvent.hpp include/Sirius/Core/Window.hpp include/Sirius/Core/Input.hpp src/Sirius/Core/Input.cpp src/Sirius/Core/Window.cpp src/Sirius/Renderer/Buffer.cpp include/Sirius/Renderer/Buffer.hpp include/Sirius/Renderer/Shader.hpp src/Sirius/Renderer/Shader.cpp include/Sirius/Renderer/RenderContext.hpp src/Sirius/Renderer/RenderContext.cpp src/Sirius/Renderer/VertexArray.cpp include/Sirius/Renderer/VertexArray.hpp src/Sirius/Core/Log.cpp include/Sirius/Core/Log.hpp include/Sirius/Core/Core.hpp src/Sirius/Core/Layer.cpp include/Sirius/Core/Layer.hpp src/Sirius/Core/LayerStack.cpp include/Sirius/Core/LayerStack.hpp src/Sirius/ImGui/ImGuiLayer.cpp include/Sirius/ImGui/ImGuiLayer.hpp vendor/imgui/backends/imgui_impl_glfw.cpp vendor/imgui/backends/imgui_impl_glfw.h vendor/imgui/backends/imgui_impl_opengl3.cpp vendor/imgui/backends/imgui_impl_opengl3.h src/Sirius/Renderer/Renderer.cpp include/Sirius/Renderer/Renderer.hpp src/Sirius/Renderer/RenderCommand.cpp include/Sirius/Renderer/RenderCommand.hpp src/Sirius/Renderer/Camera.cpp include/Sirius/Renderer/Camera.hpp include/Sirius/Core/KeyCodes.h include/Sirius/Core/MouseButtonCodes.h include/Sirius/Core/Timestep.hpp src/Sirius/Renderer/CameraController.cpp include/Sirius/Renderer/CameraController.hpp src/Sirius/Renderer/Texture.cpp include/Sirius/Renderer/Texture.hpp include/Sirius/Math/Vector/Vector2.hpp include/Sirius/Math/Vector/Vector3.hpp include/Sirius/Math/Vector/Vector4.hpp include/Sirius/Math/Matrix/Matrix2.hpp include/Sirius/Math/Matrix/Matrix3.hpp include/Sirius/Math/Matrix/Matrix4.hpp include/Sirius/Math/Matrix/Matrix.hpp include/Sirius/Math/Matrix/transforms.hpp include/Sirius/Math/Vector/transforms.hpp include/Sirius/Math/Matrix/functions.hpp include/Sirius/Math/Math.hpp include/Sirius/Math/Matrix/clip_space.hpp include/Sirius/Math/functions.hpp src/Sirius/Renderer/Renderer2D.cpp include/Sirius/Renderer/Renderer2D.hpp src/Sirius/Renderer/Color.cpp include/Sirius/Renderer/Color.hpp src/Sirius/Renderer/Renderer3D.cpp include/Sirius/Renderer/Renderer3D.hpp)

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
target_precompile_headers(Sirius PUBLIC include/srspch.hpp)

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
# Install Sirius and its dependencies
# ----------------------------------------------------

install(TARGETS Sirius DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY vendor DESTINATION ${CMAKE_INSTALL_PREFIX})

# ----------------------------------------------------
# Sirius app executable
# ----------------------------------------------------

add_executable(Sirius_app app/app.cpp)
target_link_libraries(Sirius_app Sirius -static-libgcc -static-libstdc++)
