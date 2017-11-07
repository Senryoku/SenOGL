#pragma once

#include <iostream>
#include <functional>
#include <cassert>

#include <Enums.hpp>

/**
 * OpenGL context.
 * WIP 
**/
namespace Context
{
	bool init(); // Should be called once after the context is created.
	
	inline void enable(Capability c);
	inline void disable(Capability c);
	
	inline void viewport(size_t x, size_t y, size_t w, size_t h);
	inline void scissor(size_t x, size_t y, size_t w, size_t h);
	
	inline void clear(BufferBit bb = BufferBit::All);
	
	inline void drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices = nullptr);
	
	inline void enable(Capability c);
	inline void enable(Capability c, size_t idx);
	inline void disable(Capability c);
	inline void disable(Capability c, size_t idx);
	
	inline void viewport(size_t x, size_t y, size_t w, size_t h);
	inline void scissor(size_t x, size_t y, size_t w, size_t h);
	inline void clear(BufferBit bb);
	
	inline void depthFunc(DepthFunction f);
	inline void blendFunc(Factor src_f, Factor dst_f);

	inline void drawElements(Primitive primitiveType, size_t count, IndexType indexType, void* indices);

	inline void clearError();
	inline Error checkError(const std::string& msg = "");
	inline void safeCheck(std::function<void()> func, const std::string& msg = "");
	
	void APIENTRY debugCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
	
	inline void enableDebug();
}

#include <Context.inl>
