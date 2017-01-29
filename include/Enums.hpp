#pragma once

#include <type_traits>

#include <GL/gl3w.h>

/** @file
 * Set of strongly typed enums wrapping GLenum and tools to use them.
**/

/**
 * OpenGL avalaible Primitives
**/
enum class Primitive : GLenum
{
	Points                 = GL_POINTS,						///< Points
	LineStrip              = GL_LINE_STRIP,					///< LineStrip
	LineLoop               = GL_LINE_LOOP,					///< LineLoop
	Lines                  = GL_LINES,						///< Lines
	LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY, 		///< LineStripAdjacency
	LinesAdjacency         = GL_LINES_ADJACENCY,			///< LinesAdjacency
	TriangleStrip          = GL_TRIANGLE_STRIP,				///< TriangleStrip
	TriangleFan            = GL_TRIANGLE_FAN, 				///< TriangleFan
	Triangles              = GL_TRIANGLES,					///< Triangles
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,	///< TriangleStripAdjacency
	TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,		///< TrianglesAdjacency
	Patches                = GL_PATCHES						///< Patches (Tesselation)
};

/**
 * OpenGL Capabilities
 * @see Context::enable, glEnable, Context::disable, glDisable
**/
enum class Capability : GLenum
{
	Blend                      = GL_BLEND,
	ClipDistance               = GL_CLIP_DISTANCE0,
	ClipDistance0              = GL_CLIP_DISTANCE0,
	ColorLogicOp               = GL_COLOR_LOGIC_OP,
	CullFace                   = GL_CULL_FACE,
	DebugOutput                = GL_DEBUG_OUTPUT,
	DebugOutputSync            = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	DepthClamp                 = GL_DEPTH_CLAMP,
	DepthTest                  = GL_DEPTH_TEST,
	Dither                     = GL_DITHER,
	FramebufferSRGB            = GL_FRAMEBUFFER_SRGB,
	LineSmooth                 = GL_LINE_SMOOTH,
	Multisample                = GL_MULTISAMPLE,
	
	PolygonOffsetFill          = GL_POLYGON_OFFSET_FILL,
	PolygonOffsetLine          = GL_POLYGON_OFFSET_LINE,
	PolygonOffsetPoint         = GL_POLYGON_OFFSET_POINT,
	PolygonOffsetSmooth        = GL_POLYGON_SMOOTH,
	
	PrimitiveRestart           = GL_PRIMITIVE_RESTART,
	PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
	
	RasterizerDiscard          = GL_RASTERIZER_DISCARD,
	
	SampleAlphaToCoverage      = GL_SAMPLE_ALPHA_TO_COVERAGE,
	SampleAlphaToOne           = GL_SAMPLE_ALPHA_TO_ONE,
	SampleCoverage             = GL_SAMPLE_COVERAGE,
	SampleShading              = GL_SAMPLE_SHADING,
	SampleMask                 = GL_SAMPLE_MASK,
	
	ScissorTest                = GL_SCISSOR_TEST,
	StencilTest                = GL_STENCIL_TEST,
	TextureCubeMapSeamless     = GL_TEXTURE_CUBE_MAP_SEAMLESS,
	ProgramPointSize           = GL_PROGRAM_POINT_SIZE
};

enum class DepthFunction : GLenum
{
	Never    = GL_NEVER,
	Less     = GL_LESS,
	Equal    = GL_EQUAL,
	LEqual   = GL_LEQUAL,
	Greater  = GL_GREATER,
	NotEqual = GL_NOTEQUAL,
	GEquel   = GL_GEQUAL,
	Always   = GL_ALWAYS
};

/**
 * Factors for blendFunc. 
**/
enum class Factor : GLenum
{
	Zero					 = GL_ZERO,
	One						 = GL_ONE,
	SrcColor				 = GL_SRC_COLOR,
	OneMinusSrcColor		 = GL_ONE_MINUS_SRC_COLOR,
	DstColor				 = GL_DST_COLOR,
	OneMinusDstColor		 = GL_ONE_MINUS_DST_COLOR,
	SrcAlpha				 = GL_SRC_ALPHA,
	OneMinusSrcAlpha		 = GL_ONE_MINUS_SRC_ALPHA,
	DstAlpha				 = GL_DST_ALPHA,
	OneMinusDstAlpha		 = GL_ONE_MINUS_DST_ALPHA,
	ConstantColor			 = GL_CONSTANT_COLOR,
	OneMinusConstantColor	 = GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha			 = GL_CONSTANT_ALPHA, 
	OneMinusConstantAlpha	 = GL_ONE_MINUS_CONSTANT_ALPHA,
	
	SrcAlphaSaturate		 = GL_SRC_ALPHA_SATURATE		///< Source factor only
};

/**
 * Types supported by OpenGL. 
**/
enum class Type : GLenum
{
	Byte      = GL_BYTE,
	UByte     = GL_UNSIGNED_BYTE,
	Short     = GL_SHORT,
	UShort    = GL_UNSIGNED_SHORT,
	Int       = GL_INT,
	UInt      = GL_UNSIGNED_INT,
	Fixed     = GL_FIXED,
	HalfFloat = GL_HALF_FLOAT,
	Float     = GL_FLOAT,
	Double    = GL_DOUBLE
};

/**
 * Types of the indices for indexed drawing. 
**/
enum class IndexType : GLenum
{
	UByte  = GL_UNSIGNED_BYTE,
	UShort = GL_UNSIGNED_SHORT,
	UInt   = GL_UNSIGNED_INT
};

/**
 * Masks identifying framebuffers' buffers.
**/
enum class BufferBit : GLbitfield
{
	Color   = GL_COLOR_BUFFER_BIT,		///< Color Buffer
	Depth   = GL_DEPTH_BUFFER_BIT,		///< Depth Buffer
	Stencil = GL_STENCIL_BUFFER_BIT,	///< Stencil Buffer
	All     = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT	///< All three buffers
};

/**
 * Texture/Renderbuffer attachments.
 */
enum class Attachment : GLenum
{
	Color        = GL_COLOR_ATTACHMENT0,		///< Color Attachment 0
	Color0       = GL_COLOR_ATTACHMENT0,		///< Color Attachment 0
	Color1       = GL_COLOR_ATTACHMENT1,		///< Color Attachment 1
	Color2       = GL_COLOR_ATTACHMENT2,		///< Color Attachment 2
	Color3       = GL_COLOR_ATTACHMENT3,		///< Color Attachment 3
	Color4       = GL_COLOR_ATTACHMENT4,		///< Color Attachment 4
	Color5       = GL_COLOR_ATTACHMENT5,		///< Color Attachment 5
	Color6       = GL_COLOR_ATTACHMENT6,		///< Color Attachment 6
	Color7       = GL_COLOR_ATTACHMENT7,		///< Color Attachment 7
	Depth        = GL_DEPTH_ATTACHMENT,		    ///< Depth Attachment
	Stencil      = GL_STENCIL_ATTACHMENT,	    ///< Stencil Attachment
	DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT	///< Depth Stencil Attachment
};

/**
 * Shader types/stages.
 */
enum class ShaderType : GLenum
{
	Vertex         = GL_VERTEX_SHADER,
	TessControl    = GL_TESS_CONTROL_SHADER,
	TessEvaluation = GL_TESS_EVALUATION_SHADER,
	Geometry       = GL_GEOMETRY_SHADER,
	Fragment       = GL_FRAGMENT_SHADER,
	Compute        = GL_COMPUTE_SHADER
};

enum class Error : GLenum
{
	InvalidEnum                 = GL_INVALID_ENUM,
	InvalidValue                = GL_INVALID_VALUE,
	InvalidOperation            = GL_INVALID_OPERATION,
	InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
	OutOfMemory                 = GL_OUT_OF_MEMORY,
	NoError                     = GL_NO_ERROR
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

