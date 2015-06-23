#pragma once

#include <Shader.hpp>

/**
 * Vertex Shader
 */
class VertexShader : public Shader
{
public:
	VertexShader() =default;
	
	VertexShader(const std::string& file) 
	{
		loadFromFile(file);
	}
	
private:
	inline virtual GLenum getType() const override { return GL_VERTEX_SHADER; }
};

