# SenOGL

Little personal library to ease the use of OpenGL.
Please let me know if this is usefull to you!

## Usage

### Compilation

```
mkdir build
cd build
cmake .. 
make
```
This will compile the library to libSenOGL.a.

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
-L "path/to/SenOGL/" -lSenOGL
```
or
```
-l"path/to/SenOGL/libSenOGL.a"
```	
## Examples

Some samples can be found at https://github.com/Senryoku/

## Dependencies

* GL3W (https://github.com/skaslev/gl3w) - Included as a submodule
* stb_image, stb_image_write (https://github.com/nothings/stb) - Included

Thanks to the dev' behind these!
