#pragma once

#include <iostream>

#include <OpenGLObject.hpp>
#include <ParameterBinding.hpp>
#include <Enums.hpp>

/**
 * Describes a texture living on the GPU's memory.
 * @todo Store more information about the managed texture (type, format...)
 * 		 in order to provide easier use (image binding for example).
 * @todo Use Sampler class ?
 * @todo Parameter value enums
 * @todo DOCUMENTATION
**/
class Texture : public OpenGLObject
{
public:
	/**
	 * Scoped texture Binder.
	 * Texture is unbound at destruction and previously
	 * bound texture is restored.
	 *
	 * Should do nothing if the texture is already bound to
	 * the specified texture unit. However, this will always
	 * change the current active texture unit !
	**/
	class Binder
	{
	public:
		Binder(const Texture& t, unsigned int unit = 0);
		
		~Binder();
	private:
		GLuint				_unit = 0;
		const Texture&		_tex;
		GLuint 			_prevBound = 0;
	};

	enum class Parameter : GLenum
	{
		DepthStencilMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
		BaseLevel = GL_TEXTURE_BASE_LEVEL,
		SwizzleR = GL_TEXTURE_SWIZZLE_R, 
		SwizzleG = GL_TEXTURE_SWIZZLE_G, 
		SwizzleB = GL_TEXTURE_SWIZZLE_B,
		SwizzleA = GL_TEXTURE_SWIZZLE_A,
		// Common with Sampler
		MinFilter = GL_TEXTURE_MIN_FILTER,
		MagFilter = GL_TEXTURE_MAG_FILTER,
		MinLoD = GL_TEXTURE_MIN_LOD,
		MaxLoD = GL_TEXTURE_MAX_LOD,
		LoDBias = GL_TEXTURE_LOD_BIAS,
		WrapS = GL_TEXTURE_WRAP_S,
		WrapT = GL_TEXTURE_WRAP_T,
		WrapR = GL_TEXTURE_WRAP_R,
		BorderColor = GL_TEXTURE_BORDER_COLOR,
		CompareMode = GL_TEXTURE_COMPARE_MODE,
		CompareFunc = GL_TEXTURE_COMPARE_FUNC
	};
	
	/// @todo Complete.
	enum class PixelType : GLenum
	{
		UnsignedByte = GL_UNSIGNED_BYTE,
		UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
		UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
		UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
		HalfFloat = GL_HALF_FLOAT,
		Float = GL_FLOAT
	};
	
	Texture(PixelType pixelType = PixelType::UnsignedByte);
	
	Texture(PixelType pixelType, GLuint handle);
	
	Texture(const Texture&) =default;
	Texture(Texture&&) =default;
	Texture& operator=(const Texture&) =default;
	Texture& operator=(Texture&&) =default;
		
	virtual ~Texture();
	
	virtual void init() override;
	
	virtual void cleanup() override;
	
	inline virtual bool isValid() const override { return OpenGLObject::isValid() && isTexture(_handle); }
	
	template<typename T>
	void set(Parameter opt, T value) const
	{
		Binder B(*this);
		texParameter(getType(), static_cast<GLenum>(opt), value);
	}
	
	template<typename T>
	void setI(Parameter opt, T value) const
	{
		Binder B(*this);
		texParameterI(getType(), static_cast<GLenum>(opt), value);
	}
	
	inline PixelType getPixelType() const { return _pixelType; }
	
	void setPixelType(PixelType p);
	
	void generateMipmaps() const;
	
	virtual void bind(unsigned int unit = 0) const;
	
	virtual void unbind(unsigned int unit = 0) const;
	
	/**
	 * TODO
	**/
	virtual void bindImage(GLuint unit, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) const;
	
	inline static void activeUnit(unsigned int unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
	}
	
	/**
	 * @param unit Texture unit
	 * @return Currently bound texture at unit.
	**/
	virtual GLuint getBound(unsigned int unit = 0) const =0;
	
	/**
	 * Saves the texture as a png at path.
	 * @param path Path of the created file.
	**/
	virtual void dump(const std::string& path) const;
	
protected:
	PixelType	_pixelType = PixelType::UnsignedByte;
	
	virtual GLenum getType() const =0;
	
	inline static bool isTexture(GLuint name) { return glIsTexture(name) == GL_TRUE; }
	
	static GLenum getFormat(GLuint compCount);
	static GLuint getCompCount(GLenum format);
};
