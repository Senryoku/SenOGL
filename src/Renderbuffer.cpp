#include <Renderbuffer.hpp>

Renderbuffer::~Renderbuffer()
{
	cleanup();
}
	
void Renderbuffer::init()
{
	glGenRenderbuffers(1, &_handle);
}

void Renderbuffer::cleanup()
{
	if(_handle)
		glDeleteRenderbuffers(1, &_handle);
}

void Renderbuffer::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, _handle);
}

void Renderbuffer::create(GLsizei width, GLsizei height, GLenum internalFormat)
{
	if(_handle == 0) init();
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
	_initialized = true;
}

void Renderbuffer::storage(GLenum internalFormat, GLsizei width, GLsizei height, GLsizei samples)
{
	if(_handle == 0) init();
	bind();
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height);
	_initialized = true;
}
