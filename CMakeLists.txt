cmake_minimum_required (VERSION 2.6)

cmake_policy(SET CMP0048 OLD)

project(SenOGL)
set(SENOGL_VERSION_MAJOR 0)
set(SENOGL_VERSION_MINOR 2)

cmake_policy(SET CMP0015 NEW)

export(PACKAGE SenOGL)
  
# Libraries ------------------------------------------------------------------------

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIR})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#GL3W
add_subdirectory("external/gl3w")

# -----------------------------------------------------------------------------------

set(SOURCE_FILES
	"src/Buffer.cpp"
	"src/Context.cpp"
	"src/OpenGLObject.cpp"
	"src/ParameterBinding.cpp"
	"src/ProgramPipeline.cpp"
	"src/Query.cpp"
	"src/Renderbuffer.cpp"
	"src/TransformFeedback.cpp"
	"src/UniformBinding.cpp"
	"src/VertexArray.cpp"
	"src/shaders/ComputeShader.cpp"
	"src/shaders/FragmentShader.cpp"
	"src/shaders/GeometryShader.cpp"
	"src/shaders/Program.cpp"
	"src/shaders/Shader.cpp"
	"src/shaders/TesselationControlShader.cpp"
	"src/shaders/TesselationEvaluationShader.cpp"
	"src/shaders/VertexShader.cpp"
	"src/textures/CubeMap.cpp"
	"src/textures/Sampler.cpp"
	"src/textures/Texture.cpp"
	"src/textures/Texture2D.cpp"
	"src/textures/Texture3D.cpp"
	
	"external/stb_image/stb_image.cpp"
	"external/stb_image/stb_image_write.cpp"
)

set(SenOGL_INCLUDE_DIRECTORIES
	"include/"
	"include/shaders/"
	"include/textures/"
	
	"external/stb_image"
	"external/gl3w/include"
)

list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -Wall")

add_library(SenOGL STATIC ${SOURCE_FILES})
target_link_libraries(SenOGL gl3w ${OPENGL_LIBRARIES})
target_include_directories(SenOGL PUBLIC ${SenOGL_INCLUDE_DIRECTORIES})
