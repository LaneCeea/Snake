# Snake
I have no idea how to properly use CMake whatsoever, so the project is restricted to Visual Studio.  
Open Visual Studio, select Clone a repository and enter the link.
```
https://github.com/LaneCeea/Snake
```
Since we choose not to use the pre-compiled binaries, so we have to compile the library ourselves and it's quite some work.  
First, we have to build the GLFW submodule using CMake GUI. Source code path and building path are as following:
```
your-clone-path/Snake/Snake/vendor/glfw
your-clone-path/Snake/build
```
Configure, select Visual Studio 17 2022 as generator, change `CMAKE_CONFIGURATION_TYPES` to `Release;`, and then click generate.  
![image](https://github.com/LaneCeea/Snake/assets/109450573/dd757c96-8e89-4c51-b038-d902d5d7ae36)
Then, after building GLFW, we have to compile the GLFW library. Open `GLFW.sln` in the `build` directory and build the solution (`Ctrl+Shift+B`), it should work, well, hopefully.
