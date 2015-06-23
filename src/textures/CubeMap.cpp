#include <CubeMap.hpp>

#include <iostream>
#include <sstream>

#include <stb_image.hpp>
#include <stb_image_write.hpp>

CubeMap::CubeMap(PixelType pixelType) :
	Texture(pixelType)
{
}

void CubeMap::load(const std::array<std::string, 6>& paths, bool generateMipmaps)
{
	int x, y, n;
	std::array<void*, 6> data;
	for(size_t i = 0; i < 6; ++i)
	{
		data[i] = stbi_load(paths[i].c_str(), &x, &y, &n, 0);
		if(data[i] == nullptr)
			std::cerr << "Error Loading Texture " << paths[i] << std::endl;
	}
	create(data, x, y, n, generateMipmaps);
	for(size_t i = 0; i < 6; ++i)
		stbi_image_free(data[i]);
}

void CubeMap::create(size_t width, size_t height, GLenum internalFormat)
{
	create(nullptr, width, height, internalFormat, internalFormat, false);
}

void CubeMap::create(void* data, size_t width, size_t height, int compCount, bool generateMipmaps)
{
	create({data, data, data, data, data, data}, width, height, compCount, generateMipmaps);
}

void CubeMap::create(const std::array<void*, 6>& data, size_t width, size_t height, int compCount, bool generateMipmaps)
{
	GLenum format = getFormat(compCount);
	create(data, width, height, format, format, generateMipmaps);
}

void CubeMap::create(void* data, size_t width, size_t height, GLint internalFormat, GLenum format, bool generateMipmaps)
{
	create({data, data, data, data, data, data}, width, height, internalFormat, format, generateMipmaps);
}

void CubeMap::create(const std::array<void*, 6>& data, size_t width, size_t height, GLint internalFormat, GLenum format, bool generateMipmaps)
{
	if(_handle == 0)
		init();
	
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	
	glGenTextures(1, &_handle);
	bind();
	
	for(size_t i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
					 0,
					 internalFormat,
					 static_cast<GLsizei>(width),
					 static_cast<GLsizei>(height),
					 0,
					 format,
					 to_underlying(_pixelType),
					 data[i]);
	
	if(generateMipmaps)
		set(Parameter::MinFilter, GL_LINEAR_MIPMAP_LINEAR);
	else
		set(Parameter::MinFilter, GL_LINEAR);
	set(Parameter::MagFilter, GL_LINEAR);
	set(Parameter::MagFilter, GL_LINEAR);
	set(Parameter::WrapS, GL_CLAMP_TO_EDGE);
	set(Parameter::WrapT, GL_CLAMP_TO_EDGE);
	set(Parameter::WrapR, GL_CLAMP_TO_EDGE);

	if(generateMipmaps)
		glGenerateMipmap(getType());

	unbind();
}

void CubeMap::dump(const std::string& path) const
{
	bind();
	GLint width, height, format;
	glGetTexLevelParameteriv(getType(), 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(getType(), 0, GL_TEXTURE_HEIGHT, &height);
	glGetTexLevelParameteriv(getType(), 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
	if(_pixelType == PixelType::UnsignedByte)
	{
		GLubyte* data = nullptr;
		data = new GLubyte[getCompCount(format) * width * height];
	
		for(int i = 0; i < 6; i++)
		{
			glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, to_underlying(_pixelType), data);
			std::ostringstream oss;
			oss << path << i << ".png";
			stbi_write_png(oss.str().c_str(), width, height, getCompCount(format), data, 0);
		}
		
		delete[] data;
	} else {
	}
	unbind();
}
