cmake_minimum_required(VERSION 3.2)
project(stb_image)

set(STB_IMAGE_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp)

add_library(stb_image STATIC ${STB_IMAGE_SRC})
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.)