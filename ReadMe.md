# PlaneVS(not finish)

## Introduction

This is a plane battle game that allow two player competition with each other.

## How to compile

### required third-party libraries

* SDL2
* SDL2\_image
* SDL2\_ttf
* SDL2\_mixer
* glm
* JsonCpp

### compile notification

#### about tools  

The project use `cmake` to build.So first make sure you have cmake.  
Please **don't** use `MinGW`'s compilers.Because this project use `filesystem` in `C++17`,but MinGW don't support it currently.May be you can choose `Clang` or `msvc`.  

#### about third-party libraries

##### Unix

If you are MacOSX or Linux,please make sure that you have these libraries firstly.

##### Windows

If you are Windows,and want use package manager(eg. vcpkg),please modify the CMakeLists or cmake/xxx\_Config.cmake to add your package.  
If you don't have any package manager,cmake will use `git` to fetch necessary third libraries to directory `external/` and use it.  
Sometimes due to the network status,cmake may download third part failed,please **delete the third-party and rebuild to make cmake download again**.

### compile command

Execute these commands under root dir.
```
mkdir build
cmake -S . -B build
cmake --build build
```

