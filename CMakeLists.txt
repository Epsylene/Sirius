
# ----------------------------------------------------
# Start Sirius project
# ----------------------------------------------------

cmake_minimum_required(VERSION 3.17)
project(Sirius VERSION 0.2.0)

# Bin directory #
file(MAKE_DIRECTORY bin/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# ----------------------------------------------------
# Compiler and build configuration
# ----------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------
# Sirius library and dependencies
# ----------------------------------------------------

add_subdirectory(lib/fmt EXCLUDE_FROM_ALL)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# Assimp #
set(CMAKE_PREFIX_PATH lib/assimp/lib/cmake/assimp-5.0/)
find_package(assimp CONFIG)

# ImGui #
add_library(imgui STATIC lib/imgui/imgui_tables.cpp lib/imgui/imconfig.h lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui.h lib/imgui/imgui.cpp lib/imgui/imgui_internal.h lib/imgui/imstb_rectpack.h lib/imgui/imgui_widgets.cpp ${CMAKE_CURRENT_LIST_DIR}/lib/imgui/imstb_textedit.h ${CMAKE_CURRENT_LIST_DIR}/lib/imgui/imstb_truetype.h)
target_include_directories(imgui PUBLIC lib/imgui)

# glad #
add_library(glad STATIC lib/glad/src/glad.c lib/glad/include/glad/glad.h lib/glad/include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC lib/glad/include)

# stb_image #
add_library(stb_image STATIC lib/stb_image/stb_image.h lib/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC lib/stb_image/)

### LIBRARY ###
add_library(Sirius SHARED src/Sirius/Core/EntryPoint.hpp src/Sirius/Core/Application.cpp src/Sirius/Core/Application.hpp src/Sirius.hpp src/srspch.hpp src/Sirius/Events/Event.hpp src/Sirius/Events/KeyEvent.hpp src/Sirius/Events/ApplicationEvent.hpp src/Sirius/Events/MouseEvent.hpp src/Sirius/Core/Window.hpp src/Sirius/Core/Input/Input.hpp src/Sirius/Core/Input.cpp src/Sirius/Core/Window.cpp src/Sirius/Renderer/Utils/Buffer.cpp src/Sirius/Renderer/Utils/Buffer.hpp src/Sirius/Renderer/Utils/Shader.hpp src/Sirius/Renderer/Utils/Shader.cpp src/Sirius/Renderer/RenderContext.hpp src/Sirius/Renderer/RenderContext.cpp src/Sirius/Renderer/Utils/VertexArray.cpp src/Sirius/Renderer/Utils/VertexArray.hpp src/Sirius/Core/Logger/Log.tpp src/Sirius/Core/Logger/Log.hpp src/Sirius/Core/Core.hpp src/Sirius/Core/Layer.cpp src/Sirius/Core/Layer.hpp src/Sirius/Core/LayerStack.cpp src/Sirius/Core/LayerStack.hpp src/Sirius/UI/ImGuiLayer.cpp src/Sirius/UI/ImGuiLayer.hpp lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_glfw.h lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_opengl3.h src/Sirius/Renderer/Renderer.cpp src/Sirius/Renderer/Renderer.hpp src/Sirius/Renderer/RenderCommand.cpp src/Sirius/Renderer/RenderCommand.hpp src/Sirius/Renderer/Objects/Camera.cpp src/Sirius/Renderer/Objects/Camera.hpp src/Sirius/Core/Input/KeyCodes.h src/Sirius/Core/Input/MouseButtonCodes.h src/Sirius/Core/Timestep.hpp src/Sirius/Renderer/Objects/CameraController.cpp src/Sirius/Renderer/Objects/CameraController.hpp src/Sirius/Renderer/Utils/Texture.cpp src/Sirius/Renderer/Utils/Texture.hpp src/Sirius/Math/Vector/Vector.hpp src/Sirius/Math/Vector/Vector2.hpp src/Sirius/Math/Vector/Vector3.hpp src/Sirius/Math/Vector/Vector4.hpp src/Sirius/Math/Matrix/Matrix2.hpp src/Sirius/Math/Matrix/Matrix3.hpp src/Sirius/Math/Matrix/Matrix4.hpp src/Sirius/Math/Matrix/Matrix.hpp src/Sirius/Math/Matrix/transforms.hpp src/Sirius/Math/Vector/transforms.hpp src/Sirius/Math/Matrix/functions.hpp src/Sirius/Math/Math.hpp src/Sirius/Math/Matrix/clip_space.hpp src/Sirius/Math/functions.hpp src/Sirius/Renderer/Renderer2D.cpp src/Sirius/Renderer/Renderer2D.hpp src/Sirius/Renderer/Utils/Color.cpp src/Sirius/Renderer/Utils/Color.hpp src/Sirius/Renderer/Renderer3D.cpp src/Sirius/Renderer/Renderer3D.hpp src/Sirius/Renderer/Utils/Material.cpp src/Sirius/Renderer/Utils/Material.hpp src/Sirius/Renderer/Objects/Light.hpp src/Sirius/Renderer/Objects/Light.cpp src/Sirius/Renderer/Objects/Model.cpp src/Sirius/Renderer/Objects/Model.hpp src/Sirius/Renderer/Objects/PrefabMeshes.cpp src/Sirius/Renderer/Objects/PrefabMeshes.hpp src/Sirius/UI/Scene.cpp src/Sirius/UI/Scene.hpp src/Sirius/UI/Panels.cpp src/Sirius/UI/Panels.hpp src/Sirius/Renderer/Objects/Skybox.cpp src/Sirius/Renderer/Objects/Skybox.hpp)
target_link_libraries(Sirius PUBLIC fmt::fmt ${ASSIMP_LIBRARIES} imgui glfw ${GLFW_LIBRARIES} opengl32 glad stb_image)

# Standard library #
target_link_libraries(Sirius PUBLIC -Wl,--allow-multiple-definition -static -static-libgcc -static-libstdc++)

# Copy the Assimp DLL to the librarie's bin directory
add_custom_command(
        TARGET Sirius POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp/bin/libassimp.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libassimp.dll
)

# Precompiled headers
target_precompile_headers(Sirius PUBLIC src/srspch.hpp)

# ----------------------------------------------------
# Sirius include directories and definitions
# ----------------------------------------------------

add_definitions(-DGLFW_INCLUDE_NONE)
add_compile_definitions(SRS_LIB_DIR=${CMAKE_CURRENT_SOURCE_DIR})

set(SIRIUS_INCLUDE_DIRS src lib/fmt/include lib/imgui/ lib/glfw/include/ lib/glad/include/ lib/stb_image lib/assimp/include lib/magic_enum)
target_include_directories(Sirius PUBLIC ${SIRIUS_INCLUDE_DIRS})

# ----------------------------------------------------
# Install Sirius and its dependencies
# ----------------------------------------------------

install(TARGETS Sirius DESTINATION lib)
install(DIRECTORY src/ DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

# Dependencies #
install(FILES bin/${CMAKE_BUILD_TYPE}/libAssimp.dll DESTINATION lib/)

# ----------------------------------------------------
# Sirius test application
# ----------------------------------------------------

add_subdirectory(app)