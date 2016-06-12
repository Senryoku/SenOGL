#pragma once

#include <Shader.hpp>

/**
 * Geometry Shader
 */
class GeometryShader : public Shader
{
public:
	GeometryShader() =default;
	
	GeometryShader(const std::string& file)
	{
		loadFromFile(file);
	}

private:
	inline virtual GLenum getType() const override { return GL_GEOMETRY_SHADER; }
};

