#pragma once

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
};
