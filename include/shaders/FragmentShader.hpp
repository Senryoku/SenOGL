#pragma once

#include <Shader.hpp>

/**
 * Fragment Shader
 */
class FragmentShader : public Shader
{
public:
	FragmentShader() =default;
	
private:
	inline virtual GLenum getType() const override { return GL_FRAGMENT_SHADER; }
};
