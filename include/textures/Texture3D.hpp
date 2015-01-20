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
class Texture3D : public Texture
{
public:
	Texture3D() =default;
	
	Texture3D(PixelType pixelType) :
		Texture(pixelType)
	{
	}
	
	void create(const void* data, size_t width, size_t height, size_t depth, int compCount);
	void create(const void* data, size_t width, size_t height, size_t depth, GLint internalFormat, GLenum format, bool generateMipmaps = true);
	
	virtual GLuint getBound(unsigned int unit = 0) const override
	{
		activeUnit(unit);
		GLint r;
		glGetIntegerv(GL_TEXTURE_BINDING_3D, &r);
		return static_cast<GLuint>(r);
	}
private:	
	virtual GLenum getType() const override { return GL_TEXTURE_3D; }
};
