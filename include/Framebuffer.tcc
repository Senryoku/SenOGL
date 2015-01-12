#include <iostream>

/** @file
 * Implementation file of Framebuffer.hpp
 * @see Framebuffer.hpp
**/

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
Framebuffer<TexType, ColorCount, DepthType, UseDepth>::Framebuffer(size_t size) : 
	_width(size),
	_height(size)
{
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
Framebuffer<TexType, ColorCount, DepthType, UseDepth>::Framebuffer(size_t width, size_t height) : 
	_width(width),
	_height(height)
{
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
Framebuffer<TexType, ColorCount, DepthType, UseDepth>::~Framebuffer()
{
	cleanup();
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::cleanup()
{
	glDeleteFramebuffers(1, &_handle);
	_handle = 0;
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::init()
{
	if(_handle != 0)
		cleanup();

	glGenFramebuffers(1, &_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, _handle);
		
	if(ColorCount > 0)
	{
		GLenum DrawBuffers[ColorCount];
		for(size_t i = 0; i < ColorCount; ++i)
		{
			DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			if(!_color[i])
				_color[i].create(_width, _height, GL_RGBA);
			attach(_color[i], GL_COLOR_ATTACHMENT0 + i);
		}
		
		glDrawBuffers(ColorCount, DrawBuffers);
	} else {
		glDrawBuffer(GL_NONE);
	}
	
	if(UseDepth)
	{
		if(!_depth)
			_depth.create(_width, _height, GL_DEPTH_COMPONENT);
		attach(_depth, GL_DEPTH_ATTACHMENT);
	}
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Error while creating Framebuffer !" << std::endl;
		cleanup();
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::bind(FramebufferTarget target) const
{
	glBindFramebuffer(static_cast<GLenum>(target), _handle);
	if(target == FramebufferTarget::Read)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0); ///< @todo Do Better.
	} else {
		glViewport(0, 0, _width, _height);
	}
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::clear() const
{
	GLbitfield target = (ColorCount > 0) ? GL_COLOR_BUFFER_BIT : 0;
	if(UseDepth) target |= GL_DEPTH_BUFFER_BIT;
	glClear(target);
}
	
template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::clear(BufferBit target) const
{
	glClear(to_underlying(target));
}

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
inline void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::attach(const Texture& tex, GLenum attachment) const
{
	glFramebufferTexture(GL_FRAMEBUFFER, attachment, tex.getName(), 0);
}
	
template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
inline void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::attach(const Renderbuffer& buf, GLenum attachment) const
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buf.getName());
}
	
// Static

template<typename TexType, unsigned int ColorCount, typename DepthType, bool UseDepth>
inline void Framebuffer<TexType, ColorCount, DepthType, UseDepth>::unbind(FramebufferTarget target)
{
	glBindFramebuffer(to_underlying(target), 0);
};
