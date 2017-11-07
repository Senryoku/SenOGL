// Inline Implementation

inline void Context::enable(Capability c)
{
	glEnable(to_underlying(c));
}

inline void Context::enable(Capability c, size_t i)
{
	glEnablei(to_underlying(c), static_cast<GLuint>(i));
}

inline void Context::disable(Capability c)
{
	glDisable(to_underlying(c));
}

inline void Context::disable(Capability c, size_t i)
{
	glDisablei(to_underlying(c), static_cast<GLuint>(i));
}

inline void Context::viewport(size_t x, size_t y, size_t w, size_t h)
{
	glViewport(x, y, w, h);
}

inline void Context::scissor(size_t x, size_t y, size_t w, size_t h)
{
	enable(Capability::ScissorTest);
	glScissor(x, y, w, h);
}

inline void Context::clear(BufferBit bb)
{
	glClear(to_underlying(bb));
}

inline void Context::depthFunc(DepthFunction f)
{
	glDepthFunc(to_underlying(f));
}

inline void Context::blendFunc(Factor src_f, Factor dst_f)
{
	assert(dst_f != Factor::SrcAlphaSaturate);
	glBlendFunc(to_underlying(src_f), to_underlying(dst_f));
}

inline void Context::drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices)
{
	glDrawElements(to_underlying(primitiveType), count, to_underlying(indexType), indices);
}

inline void Context::clearError()
{
	glGetError();
}

inline Error Context::checkError(const std::string& msg)
{
	Error r = Error(glGetError());
	if(r != Error::NoError)
	{
		std::cerr << "An error occured [" << msg << "], glGetError returned ";
		switch(r)
		{
		case Error::InvalidEnum:
			std::cerr << "GL_INVALID_ENUM" << std::endl;
			break;
		case Error::InvalidValue:
			std::cerr << "GL_INVALID_VALUE" << std::endl;
			break;
		case Error::InvalidOperation:
			std::cerr << "GL_INVALID_OPERATION" << std::endl;
			break;
		case Error::InvalidFramebufferOperation:
			std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
			break;
		case Error::OutOfMemory:
			std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
			break;
		default:
			std::cerr << "an unknown value." << std::endl;
			break;
		}
	}
	return r;
}

inline void Context::safeCheck(std::function<void()> func, const std::string& msg)
{
	#ifndef NDEBUG
	clearError();
	#endif
	func();
	#ifndef NDEBUG
	checkError(msg);
	#endif
}

inline void Context::enableDebug()
{
	enable(Capability::DebugOutput);
	enable(Capability::DebugOutputSync);
	glDebugMessageCallback(debugCallback, nullptr);
	glDebugMessageControl(
	  GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true
	);
}
