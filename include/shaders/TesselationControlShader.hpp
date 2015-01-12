#pragma once

#include <Shader.hpp>

/**
 * Tesselation Control Shader
 */
class TesselationControlShader : public Shader
{
public:
	TesselationControlShader() =default;
	
private:
	inline virtual GLenum getType() const override { return GL_TESS_CONTROL_SHADER; }
};
