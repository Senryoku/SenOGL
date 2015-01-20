#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

#include <Texture.hpp>

/**
 * Texture 2D
 * @todo Add a LOT of options !
 * @todo Change default parameters ?
**/
class Texture2D : public Texture
{
public:
	Texture2D() =default;
	
	Texture2D(PixelType pixelType) :
		Texture(pixelType)
	{
	}
	
	Texture2D(const std::string& path);

	void load(const std::string& path);
	
	/**
	 * Create an uninitialized RGBA texture
	 */
	void create(size_t width, size_t height, GLenum internalFormat);
	
	void create(const void* data, size_t width, size_t height, int compCount);
	void create(const void* data, size_t width, size_t height, GLint internalFormat, GLenum format, bool generateMipmaps = true);
	
	virtual GLuint getBound(unsigned int unit = 0) const override
	{
		activeUnit(unit);
		GLint r;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &r);
		return static_cast<GLuint>(r);
	}
private:
	virtual inline GLenum getType() const override { return GL_TEXTURE_2D; }
};
