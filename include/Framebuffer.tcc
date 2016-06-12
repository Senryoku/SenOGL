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
	
	GLenum ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(ret != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Error while creating Framebuffer ! glCheckFramebufferStatus returned " << ret << " which ";
		switch(ret)
		{
			case GL_FRAMEBUFFER_UNDEFINED: 
				std::cerr << "is returned if target is the default framebuffer, but the default framebuffer does not exist." << std::endl;
                break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: 
				std::cerr << "is returned if any of the framebuffer attachment points are framebuffer incomplete." << std::endl;
                break;
	
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: 
				std::cerr << "is returned if the framebuffer does not have at least one image attached to it." << std::endl;
                break;
	
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: 
				std::cerr << "is returned if the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi." << std::endl;
                break;
	
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: 
				std::cerr << "is returned if GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER." << std::endl;
                break;
		
			case GL_FRAMEBUFFER_UNSUPPORTED: 
				std::cerr << "is returned if the combination of internal formats of the attached images violates an implementation-dependent set of restrictions." << std::endl;
                break;
	
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: 
				std::cerr << "is returned if the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES. Or, is also returned if the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures." << std::endl;
                break;
	
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: 
				std::cerr << "is returned if any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target." << std::endl;
                break;
				
			default:
				std::cerr << "is an unknown error." << std::endl;
		}
		cleanup();
	}
	
	unbind();
}

template<typename _CT, unsigned int _CC, typename _DT, bool _UD, bool _US>
void Framebuffer<_CT, _CC, _DT, _UD, _US>::bind(FramebufferTarget target, Attachment readAttach) const
{
	glBindFramebuffer(to_underlying(target), _handle);
	if(target == FramebufferTarget::Read)
	{
		glReadBuffer(to_underlying(readAttach));
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
