#include <TransformFeedback.hpp>

TransformFeedback::~TransformFeedback()
{
	cleanup();
}

void TransformFeedback::init()
{
	cleanup();
	glGenTransformFeedbacks(1, &_handle);
}

void TransformFeedback::cleanup()
{
	if(_handle)
		glDeleteTransformFeedbacks(1, &_handle);
}

void TransformFeedback::bindBuffer(GLuint index, const Buffer& buffer, GLintptr offset, GLsizeiptr size)
{
	bind();
	buffer.bind(Buffer::Target::TransformFeedback, index, offset, size);
}
