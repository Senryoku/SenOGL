#pragma once

#include <Shader.hpp>

/**
 * Geometry Shader
 */
class GeometryShader : public Shader
{
public:
	GeometryShader() =default;

private:
	inline virtual GLenum getType() const override { return GL_GEOMETRY_SHADER; }
};

