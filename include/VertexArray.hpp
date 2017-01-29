#pragma once

#include <OpenGLObject.hpp>
#include <Buffer.hpp>

/**
 * Vertex Array Object (VAO)
 *
**/
class VertexArray : public OpenGLObject
{
public:
	virtual ~VertexArray();
	
	virtual void init() override; 
	
	/// Destroys the OpenGLObject. 
	virtual void cleanup() override;
	
	/// Binds the VAO.
	void bind() const;

	/// Unbind any VAO currently bound.
	static void unbind();
	
	/// glVertexAttribPointer
	void attribute(size_t index, size_t size, Type type, bool normalized, size_t stride, const void* pointer = nullptr) const;
	
	/// Helper for setting attributes of a bound VBO (offset instead of a pointer to the first value)
	inline void attribute(size_t index, size_t size, Type type, bool normalized, size_t stride, size_t offset) const;
	
	/// glVertexAttribPointerI
	void attributeI(size_t index, size_t size, Type type, size_t stride, const void* pointer = nullptr) const;
private:
};

void VertexArray::attribute(size_t index, size_t size, Type type, bool normalized, size_t stride, size_t offset) const
{
	attribute(index, size, type, normalized, stride, reinterpret_cast<const void*>(offset));
}
