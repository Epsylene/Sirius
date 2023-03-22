cmake_minimum_required(VERSION 3.2)
project(glad)

set(GLAD_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h)

add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)