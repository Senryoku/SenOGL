#pragma once

#include <type_traits>

#define GLEW_STATIC
#include <GL/glew.h>

/** @file
 * Set of strongly typed enums wrapping GLenum and tools to use them.
**/

/**
 * OpenGL avalaible Primitives
**/
enum class Primitive : GLenum
{
	Points = GL_POINTS, 									///< Points
	LineStrip = GL_LINE_STRIP, 								///< LineStrip
	LineLoop = GL_LINE_LOOP, 								///< LineLoop
	Lines = GL_LINES, 										///< Lines
	LineStripAdjacency = GL_LINE_STRIP_ADJACENCY, 			///< LineStripAdjacency
	LinesAdjacency = GL_LINES_ADJACENCY, 					///< LinesAdjacency
	TriangleStrip = GL_TRIANGLE_STRIP, 						///< TriangleStrip
	TriangleFan = GL_TRIANGLE_FAN, 							///< TriangleFan
	Triangles = GL_TRIANGLES, 								///< Triangles
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,	///< TriangleStripAdjacency
	TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,			///< TrianglesAdjacency
	Patches = GL_PATCHES									///< Patches (Tesselation)
};

/**
 * Convenient cast to the underlying type of an enum
 * @param e Value to cast
**/
template <typename E>
typename std::underlying_type<E>::type to_underlying(E e)
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}
