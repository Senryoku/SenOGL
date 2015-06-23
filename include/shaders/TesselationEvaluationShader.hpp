#pragma once

#include <Shader.hpp>

/**
 * Tesselation Evaluation Shader
 */
class TesselationEvaluationShader : public Shader
{
public:
	TesselationEvaluationShader() =default;
	
	TesselationEvaluationShader(const std::string& file)
	{
		loadFromFile(file);
	}
	
private:	
	inline virtual GLenum getType() const override { return GL_TESS_EVALUATION_SHADER; }
};

