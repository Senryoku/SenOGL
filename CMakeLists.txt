cmake_minimum_required (VERSION 2.6)

cmake_policy(SET CMP0048 OLD)

project (SenOGL)
set (SENOGL_VERSION_MAJOR 0)
set (SENOGL_VERSION_MINOR 2)

cmake_policy(SET CMP0015 NEW)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

export(PACKAGE SenOGL)
  
# Libraries ------------------------------------------------------------------------

#OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
#MESSAGE(STATUS "OpenGL Found ? ${OPENGL_FOUND}")
INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIR})
LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})
ADD_DEFINITIONS(${OpenGL_DEFINITIONS})

#GL3W
SET(GL3W_INCLUDE_DIR "../gl3w/include" CACHE FILEPATH "GL3W_INCLUDE_DIR")
SET(GL3W_LIBRARY_DIRS "../gl3w" CACHE FILEPATH "GL3W_LIBRARY_DIRS")
INCLUDE_DIRECTORIES(${GL3W_INCLUDE_DIR})
LINK_DIRECTORIES(${GL3W_LIBRARY_DIRS})

#GLM
SET(GLM_INCLUDE_DIR "../glm" CACHE FILEPATH "GLM_INCLUDE_DIR")
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR})

# -----------------------------------------------------------------------------------

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

MACRO(REC_SOURCE ParentDir)
	AUX_SOURCE_DIRECTORY(${ParentDir} SOURCE_FILES)
	
	SUBDIRLIST(SUBDIRECTORIES ${ParentDir})

	foreach(DIR ${SUBDIRECTORIES})
		REC_SOURCE(${ParentDir}/${DIR})
		
	endforeach(DIR)
ENDMACRO()

REC_SOURCE(${CMAKE_SOURCE_DIR}/src)
REC_SOURCE(${CMAKE_SOURCE_DIR}/include)
REC_SOURCE(${CMAKE_SOURCE_DIR}/external)

MACRO(REC_INCLUDE ParentDir)
	INCLUDE_DIRECTORIES(${ParentDir})
	
	SUBDIRLIST(SUBDIRECTORIES ${ParentDir})

	foreach(DIR ${SUBDIRECTORIES})
		REC_INCLUDE(${ParentDir}/${DIR})
		
	endforeach(DIR)
ENDMACRO()

REC_INCLUDE(${CMAKE_SOURCE_DIR}/include)
REC_INCLUDE(${CMAKE_SOURCE_DIR}/external)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x  -Wall ${CMAKE_CXX_FLAGS}")

add_library(SenOGL STATIC ${SOURCE_FILES})
