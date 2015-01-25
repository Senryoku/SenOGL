#include <iostream>

#include <Context.hpp>

/** @file
 * Implementation file of Framebuffer.hpp
 * @see Framebuffer.hpp
**/

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
Framebuffer<_CT, _CC, _DT, _UD, _US>::Framebuffer(size_t size) : 
	_width(size),
	_height(size)
{
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
Framebuffer<_CT, _CC, _DT, _UD, _US>::Framebuffer(size_t width, size_t height) : 
	_width(width),
	_height(height)
{
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
Framebuffer<_CT, _CC, _DT, _UD, _US>::~Framebuffer()
{
	cleanup();
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::cleanup()
{
	glDeleteFramebuffers(1, &_handle);
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::init()
{
	if(_handle != 0)
		cleanup();

	glGenFramebuffers(1, &_handle);
	bind();
		
	if(_CC > 0)
	{
		GLenum DrawBuffers[_CC];
		for(size_t i = 0; i < _CC; ++i)
		{
			DrawBuffers[i] = to_underlying(Attachment::Color) + i;
			if(!_color[i])
				_color[i].create(_width, _height, GL_RGBA);
			attach(_color[i], attachmentColor(i));
		}
		
		glDrawBuffers(_CC, DrawBuffers);
	} else {
		glDrawBuffer(GL_NONE);
	}
	
	if(_UD)
	{
		if(_US)
		{
			if(!_depth[0])
				_depth[0].create(_width, _height, GL_DEPTH24_STENCIL8);
			attach(_depth[0], Attachment::DepthStencil);
		} else {
			if(!_depth[0])
				_depth[0].create(_width, _height, GL_DEPTH_COMPONENT);
			attach(_depth[0], Attachment::Depth);
		}
	}
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Error while creating Framebuffer !" << std::endl;
		cleanup();
	}
	
	unbind();
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::bind(FramebufferTarget target) const
{
	glBindFramebuffer(to_underlying(target), _handle);
	if(target == FramebufferTarget::Read)
	{
		glReadBuffer(to_underlying(Attachment::Color)); ///< @todo Do Better.
	} else {
		Context::viewport(0, 0, _width, _height);
	}
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::clear() const
{
	GLbitfield target = (_CC > 0) ? GL_COLOR_BUFFER_BIT : 0;
	if(_UD) target |= GL_DEPTH_BUFFER_BIT;
	bind();
	glClear(target);
}
	
template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline _CT& Framebuffer<_CT, _CC, _DT, _UD, _US>::getColor(unsigned int i)
{
	static_assert(_CC > 0, "This framebuffer has no color attachment.");
	assert(i < _CC);
	return _color[i];
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline _DT& Framebuffer<_CT, _CC, _DT, _UD, _US>::getDepth()
{
	static_assert(_UD, "This framebuffer has no depth attachment.");
	assert(_UD);
	return _depth[0];
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline const _CT& Framebuffer<_CT, _CC, _DT, _UD, _US>::getColor(unsigned int i) const
{
	static_assert(_CC > 0, "This framebuffer has no color attachment.");
	assert(i < _CC); 
	return _color[i];
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline const _DT& Framebuffer<_CT, _CC, _DT, _UD, _US>::getDepth() const
{
	static_assert(_UD, "This framebuffer has no depth attachment.");
	assert(_UD);
	return _depth[0];
}
	
template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::clear(BufferBit target) const
{
	bind();
	glClear(to_underlying(target));
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline void Framebuffer<_CT, _CC, _DT, _UD, _US>::attach(const Texture& tex, Attachment attachment) const
{
	bind();
	glFramebufferTexture(GL_FRAMEBUFFER, to_underlying(attachment), tex.getName(), 0);
}
	
template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline void Framebuffer<_CT, _CC, _DT, _UD, _US>::attach(const Renderbuffer& buf, Attachment attachment) const
{
	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, to_underlying(attachment), GL_RENDERBUFFER, buf.getName());
}
	
// Static

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
inline void Framebuffer<_CT, _CC, _DT, _UD, _US>::unbind(FramebufferTarget target)
{
	glBindFramebuffer(to_underlying(target), 0);
};

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
Attachment Framebuffer<_CT, _CC, _DT, _UD, _US>::attachmentColor(unsigned int i)
{
	return static_cast<Attachment>(GL_COLOR_ATTACHMENT0 + i);
}
