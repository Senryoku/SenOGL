#pragma once

#include <iostream>

#include <OpenGLObject.hpp>
#include <Enums.hpp>
#include <ParameterBinding.hpp>

/**
 * Describes a Sampler object.
 * @todo Parameter value enums.
**/
class Sampler : public OpenGLObject
{
public:
	/**
	 *  Sampler parameters.
	 */
	enum class Parameter : GLenum
	{
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

	/**
	 *  Default constructor.
	 */
	Sampler() =default;
	
	/**
	 *  Constructor from an existing sampler name.
	 *  @param handle OpenGL name for an existing sampler.
	 */
	Sampler(GLuint handle);
	
	Sampler(const Sampler&) =default;
	Sampler(Sampler&&) =default;
	Sampler& operator=(const Sampler&) =default;
	Sampler& operator=(Sampler&&) =default;
		
	virtual ~Sampler();

	/**
	 *  Binds the sampler to the unit texture 'unit'.
	 *  @param unit Unit Texture
	 */
	void bind(unsigned int unit = 0) const;
	
	/**
	 *  Unbinds any currently bound sampler to the unit texture 'unit'.
	 *  @param unit Unit Texture
	 */
	void unbind(unsigned int unit = 0) const;
	
	/**
	 * Set the parameter opt for value for this sampler
	 * @param opt Sampler parameter.
	 * @param value New value for opt.
	 */
	template<typename T>
	void set(Parameter opt, T value) const
	{
		samplerParameter(_handle, to_underlying(opt), value);
	}
	
	/**
	 * Set the parameter opt for value for this sampler
	 * @param opt Sampler parameter.
	 * @param value New value for opt.
	 */
	template<typename T>
	void setI(Parameter opt, T value) const
	{
		samplerParameterI(_handle, to_underlying(opt), value);
	}
	
	inline virtual bool isValid() const override { return OpenGLObject::isValid() && isSampler(_handle); }
	
protected:
	void cleanup();
	
	inline static bool isSampler(GLuint name) { return glIsSampler(name) == GL_TRUE; }
};
