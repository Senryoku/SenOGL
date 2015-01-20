#pragma once

#include <array>
#include <string>

#include <Texture.hpp>

class CubeMap : public Texture
{
public:
	CubeMap() =default;
	CubeMap(PixelType pixelType);
	
	/**
	 * Order : XPOS, XNEG, YPOS, YNEG, ZPOS, ZNEG
	**/
	void load(const std::array<std::string, 6>& paths, 
			  bool generateMipmaps = true);
	
	void create(size_t width, size_t height, GLenum internalFormat);
	
	void create(void* data,
				size_t width, 
				size_t height,
				int compCount, 
				bool generateMipmaps = true);

	void create(const std::array<void*, 6>& data,
				size_t width, 
				size_t height,
				int compCount, 
				bool generateMipmaps = true);

	void create(void* data,
				size_t width, 
				size_t height,
				GLint internalFormat, 
				GLenum format, 
				bool generateMipmaps = true);
				
	void create(const std::array<void*, 6>& data,
				size_t width, 
				size_t height,
				GLint internalFormat, 
				GLenum format, 
				bool generateMipmaps = true);
	
	virtual GLuint getBound(unsigned int unit = 0) const override
	{
		activeUnit(unit);
		GLint r;
		glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &r);
		return static_cast<GLuint>(r);
	}

	virtual void dump(const std::string& path) const override;
private:
	virtual GLenum getType() const override { return GL_TEXTURE_CUBE_MAP; }
};
