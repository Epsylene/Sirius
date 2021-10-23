![Sirius logo](imgs/Sirius.png)

# Sirius

![downloads](https://img.shields.io/github/downloads/epsylene/Sirius/total?style=flat-square)
![version](https://img.shields.io/github/v/release/epsylene/Sirius?color=blue&label=version&style=flat-square)

![A window containing several panels with options and a scene containing objects.](imgs/app.png "Sirius app window")

## Introduction

*Sirius* is a general-purpose, 
3D-oriented graphics library based 
on OpenGL. It serves mainly as a 
tool to learn graphics programming, 
but is intended on the long term to
be powerful and simple enough to be
used as a graphics engine for games,
3D rendering or physics simulations.

## Installation
### Getting started

The library is untested on any development
environment other than Windows with MinGW-w64. C++20
support is required.

### Building from sources

To build the library, you will first have
to make sure that you have the last version
of CMake installed on your computer. If
that isn't the case, you can download the 
binaries [here](https://cmake.org/download/).

Then, you will have to download the library
sources. You can click on the **Code** button
on the upper-right corner and either download
the repository's ZIP file, or clone
it with the command :

```shell
git clone https://github.com/Epsylene/Sirius.git
```

Then you have to tell CMake to generate
the configuration files for your compiler,
as well as the installation prefix for the
library files. You can do it with the CMake
GUI, or via the CLI. In the last case, the
command looks like this :

```shell
cmake -G "GENERATOR" -DCMAKE_INSTALL_PREFIX="LIBRARY_PATH" SOURCE_DIR
```

You have :
* GENERATOR : determines for which
  compiler the makefiles are going to be 
  generated (on Windows, if you are using
  MinGW or MinGW-w64, use "MinGW Makefiles";
  if you are using Visual Studio, you can search for 
  your version's CMake generator, but it should be the
  one chosen by default)
  
* LIBRARY_PATH : the path where you want
  to install the library. Make sure it 
  already exists, CMake will not create
  the folder for you !
  
* SOURCE_DIR : the path of the cloned
  repository's folder.
  
After that, the last thing you have to 
do is running this command :

```shell
mingw32-make & mingw32-make install
```

If you got no errors, then, congratulations ! You have succesfuly 
installed the library.

### Linking the library

All you need is in the library install path.
Copy-paste it into your project, and add the
following lines to your CMakeLists.txt :

```cmake
add_definitions(-DGLFW_INCLUDE_NONE)

include_directories(Sirius/include)
include_directories(Sirius/vendor/spdlog/include/)
include_directories(Sirius/vendor/imgui/)
include_directories(Sirius/vendor/glfw/include/)
include_directories(Sirius/vendor/glad/include/)
include_directories(Sirius/vendor/stb_image)
include_directories(vendor/assimp/include)
```

Change the `add_executable()` part so
it looks like this :

```cmake
link_directories(${CMAKE_SOURCE_DIR}/build)
add_executable(test app.cpp)
target_link_libraries(test PUBLIC Sirius)
```

Finally, go to *"Sirius/lib"*, *"Sirius/vendor/glfw/bin"* and *"Sirius/vendor/assimp/bin"*, grab
the *libSirius.dll*, *glfw3.dll* and *libassimp.dll*, and paste them next to
your executable. Everything should work now : you can verify
it with the *test* folder in the library source directory, which
should create an app looking like the header image.

## Credits

The library's core features were at first
derived from [The Cherno's
Game Engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT),
which is a great ressource not only on
the technicalities of a game engine,
but also the design issues that are faced
when writing a library. On the other hand, 
Joey de Vrie's [Learn OpenGL](https://learnopengl.com/) 
has been extremely useful to understand the OpenGL concepts
and objects I wanted to implement. Make sure to go check both !

Sirius uses OpenGL, [glad](https://glad.dav1d.de/), [GLFW](https://www.glfw.org/),
[Assimp](https://www.assimp.org/), [Dear ImGui](https://github.com/ocornut/imgui) 
and [spdlog](https://github.com/gabime/spdlog).
