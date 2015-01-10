#include <TransformFeedback.hpp>

TransformFeedback::~TransformFeedback()
{
	cleanup();
}

void TransformFeedback::init()
{
	if(_handle != 0)
		cleanup();
	glGenTransformFeedbacks(1, &_handle);
}

void TransformFeedback::cleanup()
{
	glDeleteTransformFeedbacks(1, &_handle);
}

void TransformFeedback::bindBuffer(GLuint index, const Buffer& buffer, GLintptr offset, GLsizeiptr size)
{
	bind();
	buffer.bind(Buffer::Type::TransformFeedback, index, offset, size);
}
