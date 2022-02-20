cmake_minimum_required(VERSION 3.17)
project(Sirius)

file(MAKE_DIRECTORY bin/${CMAKE_BUILD_TYPE}/)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Sirius)
add_subdirectory(app)
