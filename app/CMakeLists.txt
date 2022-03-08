
cmake_minimum_required(VERSION 3.17)
project(App)

add_definitions(-DGLFW_INCLUDE_NONE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_executable(Sirius_app app.cpp)
target_link_libraries(Sirius_app Sirius)
target_compile_definitions(Sirius PUBLIC -DSRS_APP_DIR=${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Sirius_app PUBLIC ${SIRIUS_INCLUDE_DIRS})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Og")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")
endif()

set(SIRIUS_BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_custom_command(
        TARGET Sirius_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SIRIUS_BIN_DIR}/libassimp.dll
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libassimp.dll
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/libfmtd.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libfmtd.dll
    )

    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/glfw3d.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glfw3d.dll
    )

    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/libSiriusd.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libSiriusd.dll
    )
else()
    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/libSirius.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libSirius.dll
    )

    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/libfmt.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libfmt.dll
    )

    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SIRIUS_BIN_DIR}/glfw3.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glfw3.dll
    )

    add_custom_command(
            TARGET Sirius_app POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/res/imgui.ini
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/imgui.ini
    )
endif()