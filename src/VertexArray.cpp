#include <VertexArray.hpp>

#include <cassert>

VertexArray::~VertexArray()
{
	cleanup();
}

void VertexArray::cleanup()
{
	glDeleteVertexArrays(1, &_handle);
	_handle = 0;
}

void VertexArray::init()
{
	if(_handle != 0)
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

void VertexArray::attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::attributeI(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) const
{
	assert(type == GL_BYTE || type == GL_UNSIGNED_BYTE || type == GL_SHORT ||
			type == GL_UNSIGNED_SHORT || type == GL_INT || type == GL_UNSIGNED_INT);
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, type, stride, pointer);
}
