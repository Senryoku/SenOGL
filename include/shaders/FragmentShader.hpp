#pragma once

#include <Shader.hpp>

/**
 * Fragment Shader
 */
class FragmentShader : public Shader
{
public:
	FragmentShader() =default;
	
	/**
	 * Construct and load shader from a file
	**/
	FragmentShader(const std::string& file)
	{
		loadFromFile(file);
	}
	
private:
	inline virtual GLenum getType() const override { return GL_FRAGMENT_SHADER; }
};

