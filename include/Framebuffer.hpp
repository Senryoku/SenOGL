#pragma once

#include <Enums.hpp>
#include <Texture.hpp>
#include <Texture2D.hpp>
#include <Renderbuffer.hpp>

/**
 * Describes the targets a framebuffer can be bound to.
**/
enum class FramebufferTarget : GLenum
{
	All = GL_FRAMEBUFFER,		///< Draw & Read target
	Draw = GL_DRAW_FRAMEBUFFER,	///< Draw target
	Read = GL_READ_FRAMEBUFFER	///< Read target
};

/**
 * Masks identifying framebuffers' buffers.
**/
enum class BufferBit : GLbitfield
{
	Color = GL_COLOR_BUFFER_BIT,		///< Color Buffer
	Depth = GL_DEPTH_BUFFER_BIT,		///< Depth Buffer
	Stencil = GL_STENCIL_BUFFER_BIT,	///< Stencil Buffer
	All = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT	///< All three buffers
};

/**
 * Framebuffer Object (FBO)
 * @param TexType Type of the textures attached to the framebuffer.
 * @param ColorCount Number of Color buffers (attachments).
 * @todo More initialization options!
**/
template<typename TexType = Texture2D, unsigned int ColorCount = 1, typename DepthType = Renderbuffer, bool UseDepth = true>
class Framebuffer : public OpenGLObject
{
public:
	using depth_type = DepthType;
	using color_type = TexType;

	/**
	 * Default constructor.
	 * @param size Resolution of the framebuffer (internal textures).
	**/
	Framebuffer(size_t size = 512);
	
	/**
	 * Constructor for a rectangular framebuffer.
	 * @param width X Resolution of the framebuffer (internal textures).
	 * @param height Y Resolution of the framebuffer (internal textures).
	**/
	Framebuffer(size_t width, size_t height);
	
	/**
	 * Destructor
	**/
	virtual ~Framebuffer();
	
	/**
	 * Initialize the OpenGLObject
	**/
	virtual void init() override;
	
	/**
	 * Destroys OpenGL object.
	**/
	virtual void cleanup() override;
	
	/**
	 * Bind this framebuffer
	 * @param target (FramebufferTarget::)Draw, Read or All
	**/
	void bind(FramebufferTarget target = FramebufferTarget::All) const;
	
	/**
	 * Clear the framebuffer.
	 * Equivalent to a call to clear(GLenum target) with
	 * Buffer::Color if any color buffer is attached to it, and
	 * Buffer::Depth if using depth.
	 * @see clear(GLenum target)
	 * @see glClear
	**/
	void clear() const;
	
	/**
	 * Clear the framebuffer.
	 * @param target Combinaison of Buffer
	 * @see clear()
	 * @see glClear
	**/
	void clear(BufferBit target) const;
	
	/**
	 * @param i Index of the color buffer.
	 * @return Texture attachment to ith color buffer.
	**/
	inline TexType& getColor(unsigned int i = 0) { return _color[i]; }
	
	/**
	 * @return Texture of the Depth buffer.
	**/
	inline TexType& getDepth() { return _depth; }
	
	/**
	 * @param i Index of the color buffer.
	 * @return Texture attachment to ith color buffer.
	**/
	inline const TexType& getColor(unsigned int i = 0) const { return _color[i]; }
	
	/**
	 * @return Texture of the Depth buffer.
	**/
	inline const DepthType& getDepth() const { return _depth; }
	
	/**
	 * @return Width of the framebuffer.
	**/
	inline size_t getWidth() const { return _width; }
	
	/**
	 * @return Height of the framebuffer.
	**/
	inline size_t getHeight() const { return _height; }

	inline void attach(const Texture& tex, GLenum attachment) const;
	
	inline void attach(const Renderbuffer& buf, GLenum attachment) const;
	
	/**
	 * Unbind any FBO currently bound to target.
	 * (Restore default framebuffer)
	 * @param target Target
	**/
	static inline void unbind(FramebufferTarget target = FramebufferTarget::All);
private:
	size_t	_width = 512;	///< Width of the framebuffer.
	size_t	_height = 512;	///< Height of the framebuffer.
	
	std::array<TexType, ColorCount>	_color;	///< Textures/Buffers attached to the color buffers.
	
	DepthType						_depth;	///< Texture/Buffer attached to the depth buffer
};

#include <Framebuffer.tcc>
