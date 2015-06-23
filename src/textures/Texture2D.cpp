#include <Texture2D.hpp>

#include <iostream>
#include "stb_image.hpp"

Texture2D::Texture2D(const std::string& path)
{
	load(path);
}
	
void Texture2D::load(const std::string& Path)
{
	int x, y, n;
	unsigned char *data = stbi_load(Path.c_str(), &x, &y, &n, 0);
	if(data == nullptr)
		std::cerr << "Error Loading Texture " << Path << std::endl;
	create(data, x, y, n);
	stbi_image_free(data);
}

void Texture2D::create(size_t width, size_t height, GLenum internalFormat)
{	
	create(nullptr, width, height, internalFormat, internalFormat, false);
}

void Texture2D::create(const void* data, size_t width, size_t height, int compCount)
{	
	GLenum format = getFormat(compCount);
	create(data, width, height, format, format);
}

void Texture2D::create(const void* data, size_t width, size_t height, GLint internalFormat, GLenum format, bool generateMipmaps)
{
	if(_handle == 0)
		init();
	
	bind();
	
	glTexImage2D(getType(), 
				 0,
				 internalFormat,
	 			 static_cast<GLsizei>(width),
				 static_cast<GLsizei>(height),
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
	set(Parameter::WrapS, GL_REPEAT);
	set(Parameter::WrapT, GL_REPEAT);

	if(generateMipmaps)
		glGenerateMipmap(getType());

	unbind();
}
