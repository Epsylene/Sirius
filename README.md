# Sirius
## Introduction

*Sirius* is a general-purpose, 
3D-oriented graphics library based 
on OpenGL. It serves mainly as a 
tool to learn graphics programming, 
but is intended on the long term to
be powerful and simple enough to be
used as a graphics engine for games,
3D rendering or physics simulations.

For the moment, the core features of *Sirius* are
for the most part derived from [The Cherno's
Game Engine series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT),
which is a great ressource not only on
the technicalities of a game engine,
but also the design issues that are faced
when writing a library. Make sure to go check it !

## Installation
### Getting started

The library is untested on any development
environment other than Windows with MinGW-w64. C++17
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
include_directories(Sirius/vendor/glm)
include_directories(Sirius/vendor/stb_image)
```

Change the `add_executable()` part so
it looks like this :

```cmake
link_directories(build)
add_executable(test main.cpp)
target_link_libraries(test PUBLIC Sirius)
```

Finally, go to *"Sirius/lib"* and *"Sirius/vendor/glfw/bin"*, grab
the *libSirius.dll* and *glfw3.dll*, and paste them next to
your executable. Everything should work now : you can verify
it with the *test* folder in the library source directory, which
should create a window with an image in it.
