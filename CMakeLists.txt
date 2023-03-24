
# ----------------------------------------------------
# Start Sirius project
# ----------------------------------------------------

cmake_minimum_required(VERSION 3.17)
project(Sirius VERSION 0.2.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# Bin directory #
file(MAKE_DIRECTORY bin/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# ----------------------------------------------------
# Compiler and build configuration
# ----------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------
# Sirius library and dependencies
# ----------------------------------------------------

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glad EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/stb_image EXCLUDE_FROM_ALL)
add_subdirectory(lib/fmt EXCLUDE_FROM_ALL)
add_subdirectory(lib/rapidobj EXCLUDE_FROM_ALL)

# Assimp #
set(CMAKE_PREFIX_PATH lib/assimp/lib/cmake/assimp-5.0/)
find_package(assimp CONFIG)

# ImGui #
add_library(imgui STATIC lib/imgui/imgui_tables.cpp lib/imgui/imconfig.h lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui.h lib/imgui/imgui.cpp lib/imgui/imgui_internal.h lib/imgui/imstb_rectpack.h lib/imgui/imgui_widgets.cpp ${CMAKE_CURRENT_LIST_DIR}/lib/imgui/imstb_textedit.h ${CMAKE_CURRENT_LIST_DIR}/lib/imgui/imstb_truetype.h)
target_include_directories(imgui PUBLIC lib/imgui)

### LIBRARY ###
add_library(Sirius SHARED src/Core/EntryPoint.hpp src/Core/Application.cpp src/Core/Application.hpp src/Sirius.hpp src/srspch.hpp src/Events/Event.hpp src/Events/KeyEvent.hpp src/Events/ApplicationEvent.hpp src/Events/MouseEvent.hpp src/Core/Window.hpp src/Core/Input/Input.hpp src/Core/Input.cpp src/Core/Window.cpp src/Renderer/Utils/Buffer.cpp src/Renderer/Utils/Buffer.hpp src/Renderer/Utils/Shader.hpp src/Renderer/Utils/Shader.cpp src/Renderer/RenderContext.hpp src/Renderer/RenderContext.cpp src/Renderer/Utils/VertexArray.cpp src/Renderer/Utils/VertexArray.hpp src/Core/Logger/Logger.tpp src/Core/Logger/Logger.hpp src/Core/Core.hpp src/Core/Layer.cpp src/Core/Layer.hpp src/Core/LayerStack.cpp src/Core/LayerStack.hpp src/UI/ImGuiLayer.cpp src/UI/ImGuiLayer.hpp lib/imgui/backends/imgui_impl_glfw.cpp lib/imgui/backends/imgui_impl_glfw.h lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_opengl3.h src/Renderer/Renderer.cpp src/Renderer/Renderer.hpp src/Renderer/RenderCommand.cpp src/Renderer/RenderCommand.hpp src/Renderer/Objects/Camera.cpp src/Renderer/Objects/Camera.hpp src/Core/Input/KeyCodes.h src/Core/Input/MouseButtonCodes.h src/Core/Timestep.hpp src/Renderer/Objects/CameraController.cpp src/Renderer/Objects/CameraController.hpp src/Renderer/Utils/Texture.cpp src/Renderer/Utils/Texture.hpp src/Math/Math.hpp src/Renderer/Renderer2D.cpp src/Renderer/Renderer2D.hpp src/Renderer/Utils/Color.cpp src/Renderer/Utils/Color.hpp src/Renderer/Renderer3D.cpp src/Renderer/Renderer3D.hpp src/Renderer/Utils/Material.cpp src/Renderer/Utils/Material.hpp src/Renderer/Objects/Light.hpp src/Renderer/Objects/Light.cpp src/Renderer/Objects/Model.cpp src/Renderer/Objects/Model.hpp src/Renderer/Objects/PrefabMeshes.cpp src/Renderer/Objects/PrefabMeshes.hpp src/UI/Scene.cpp src/UI/Scene.hpp src/UI/Panels.cpp src/UI/Panels.hpp src/Renderer/Objects/Skybox.cpp src/Renderer/Objects/Skybox.hpp src/Math/matrix_functions.hpp src/Math/matrix_functions.cpp src/Math/functions.cpp src/Math/functions.hpp src/Math/vector_functions.cpp src/Math/vector_functions.hpp)
target_link_libraries(Sirius PUBLIC fmt::fmt ${ASSIMP_LIBRARIES} imgui glfw ${GLFW_LIBRARIES} opengl32 glad stb_image glm rapidobj::rapidobj)

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