# Snake
I have no idea how to properly use CMake whatsoever, so the project is restricted to Visual Studio.  
Open Visual Studio, select Clone a repository and enter the link.
```
https://github.com/LaneCeea/Snake
```
Since we choose not to use the pre-compiled binaries, so we have to compile the library ourselves and it's quite some work.  
First, we have to build the GLFW submodule using CMake GUI. Download CMake here: https://cmake.org/  
Source code path and building path are as following:
```
your-clone-path/Snake/Snake/vendor/glfw
your-clone-path/Snake/build
```
Configure, select Visual Studio 17 2022 as generator, change `CMAKE_CONFIGURATION_TYPES` to `Debug;Release;`, and then click generate.  
![image](https://github.com/LaneCeea/Snake/assets/109450573/17a7d316-7df2-4d7c-a9c9-e024b99723d3)  
Then, after building GLFW, we have to compile the GLFW library. Open `GLFW.sln` in the `build` directory and build the solution (`Ctrl+Shift+B`) in both Debug and Release mode. It should work, well, hopefully.
