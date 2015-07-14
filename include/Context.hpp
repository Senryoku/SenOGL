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
	
	inline void drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices)
	{
		glDrawElements(to_underlying(primitiveType), count, to_underlying(indexType), indices);
	}
	
	inline GLenum checkError(const std::string& msg = "")
	{
		GLenum r = glGetError();
		if(r != GL_NO_ERROR)
		{
			std::cerr << "An error occured [" << msg << "], glGetError returned ";
			switch(r)
			{
				case GL_INVALID_ENUM:
					std::cerr << "GL_INVALID_ENUM" << std::endl;
					break;
				case GL_INVALID_VALUE:
					std::cerr << "GL_INVALID_VALUE" << std::endl;
					break;
				case GL_INVALID_OPERATION:
					std::cerr << "GL_INVALID_OPERATION" << std::endl;
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
					break;
				case GL_OUT_OF_MEMORY:
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
