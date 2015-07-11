# SenOGL

Little personal library to ease the use of OpenGL.
Please let me know if this is usefull to you!

## Usage

### Compilation

[Set GLM_INCLUDE_DIR to the path of your local copy of GLM, default is ../glm (Using cmake-gui for example)]

```
cmake . 
make
```
This will compile the library to lib/libSenOGL.a.

### Build a program using SenOGL

If you are using CMake:
```
find_package(SenOGL REQUIRED)
include_directories(${SenOGL_INCLUDE_DIRS})
link_directories(${SenOGL_LIBRARY_DIRS})
target_link_libraries(${SenOGL_LIBRARY})
```
Otherwise, add the include directory of SenOGL (assuming gcc as a compiler)
```
-I "path/to/SenOGL/include"
```
and link against libSenOGL
```
-L "path/to/SenOGL/lib" -lSenOGL
```
or
```
-l"path/to/SenOGL/lib/libSenOGL.a"
```	
## Examples

Some samples can be found at https://github.com/Senryoku/OpenGL_ToolBox

## Used Libraries

* GL3W (https://github.com/skaslev/gl3w)
* stb_image, stb_image_write (https://github.com/nothings/stb) Included
* GLM (http://glm.g-truc.net/)

Thanks to the dev' behind these!
