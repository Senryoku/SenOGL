#include <VertexArray.hpp>

#include <cassert>

VertexArray::~VertexArray()
{
	cleanup();
}

void VertexArray::cleanup()
{
	if(_handle)
	{
		glDeleteVertexArrays(1, &_handle);
		_handle = 0;
	}
}

void VertexArray::init()
{
	cleanup();
	glGenVertexArrays(1, &_handle);
}

void VertexArray::bind() const
{
	glBindVertexArray(_handle);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::attribute(size_t index, size_t size, Type type, bool normalized, size_t stride, const void* pointer) const
{
	assert(index < GL_MAX_VERTEX_ATTRIBS);
	assert(size > 0 && size <= 4);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, to_underlying(type), normalized, stride, pointer);
}

void VertexArray::attributeI(size_t index, size_t size, Type type, size_t stride, const void* pointer) const
{
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, to_underlying(type), stride, pointer);
}
