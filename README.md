# Newtonian Method Fractals

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

The project also uses [ImGUI](https://github.com/ocornut/imgui), which is already included.

This project uses OpenGL 3.3.

### Ubuntu/Linux
```bash   
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```

## Building and Running

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place   

```bash   
mkdir build   
cd build   
cmake ..   
make   
./Tutorial  
```