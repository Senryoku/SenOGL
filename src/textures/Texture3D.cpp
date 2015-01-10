#include <Texture3D.hpp>

#include <iostream>

void Texture3D::create(const void* data, size_t width, size_t height, size_t depth, int compCount)
{
	GLenum format = getFormat(compCount);
	create(data, width, height, depth, format, format);
}

void Texture3D::create(const void* data, size_t width, size_t height, size_t depth, GLint internalFormat, GLenum format, bool generateMipmaps)
{
	cleanup();
	
	glGenTextures(1, &_handle);
	bind();
	
	glTexImage3D(GL_TEXTURE_3D, 
				 0,
				 internalFormat,
	 			 static_cast<GLsizei>(width),
				 static_cast<GLsizei>(height),
				 static_cast<GLsizei>(depth),
				 0,
				 format,
				 to_underlying(_pixelType),
				 data
				); 

	// Default Parameters
	if(generateMipmaps)
		set(Parameter::MinFilter, GL_LINEAR_MIPMAP_LINEAR);
	else
		set(Parameter::MinFilter, GL_LINEAR);
	set(Parameter::MagFilter, GL_LINEAR);
	set(Parameter::WrapS, GL_CLAMP_TO_BORDER);
	set(Parameter::WrapT, GL_CLAMP_TO_BORDER);
	set(Parameter::WrapR, GL_CLAMP_TO_BORDER);
	
	// Mmh ?
	GLfloat maxAniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
	glSamplerParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
	
	if(generateMipmaps)
		glGenerateMipmap(GL_TEXTURE_3D);
	
	unbind();
}

void Texture3D::bind(unsigned int unit) const
{
	activeUnit(unit);
	glBindTexture(GL_TEXTURE_3D, _handle);
}

void Texture3D::unbind(unsigned int unit) const
{
	activeUnit(unit);
	glBindTexture(GL_TEXTURE_3D, 0);
}
