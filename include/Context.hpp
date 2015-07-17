#pragma once

#include <iostream>

#include <Enums.hpp>

/**
 * OpenGL context.
 * WIP 
**/
namespace Context
{
	inline void enable(Capability c);
	inline void disable(Capability c);
	
	inline void viewport(size_t x, size_t y, size_t w, size_t h);
	inline void scissor(size_t x, size_t y, size_t w, size_t h);
	
	inline void clear(BufferBit bb = BufferBit::All);
	
	inline void drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices = nullptr);
	
	// Inline Implementation
	
	inline void enable(Capability c)
	{
		glEnable(to_underlying(c));
	}
	
	inline void disable(Capability c)
	{
		glDisable(to_underlying(c));
	}
	
	inline void viewport(size_t x, size_t y, size_t w, size_t h)
	{
		glViewport(x, y, w, h);
	}
	
	inline void scissor(size_t x, size_t y, size_t w, size_t h)
	{
		enable(Capability::ScissorTest);
		glScissor(x, y, w, h);
	}
	
	inline void clear(BufferBit bb)
	{
		glClear(to_underlying(bb));
	}
	
	inline void drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices)
	{
		glDrawElements(to_underlying(primitiveType), count, to_underlying(indexType), indices);
	}
	
	inline Error checkError(const std::string& msg = "")
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
};
