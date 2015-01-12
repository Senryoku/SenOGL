#pragma once

#include <cassert>

#include <OpenGLObject.hpp>
#include <Enums.hpp>
#include <Program.hpp>

/**
 * OpenGL ProgramPipeline Object
**/
class ProgramPipeline : public OpenGLObject
{
public:
	enum class Stage : GLbitfield
	{
		Vertex = GL_VERTEX_SHADER_BIT,
		TesselationControl = GL_TESS_CONTROL_SHADER_BIT,
		TesselationEvaluation = GL_TESS_EVALUATION_SHADER_BIT,
		Geometry = GL_GEOMETRY_SHADER_BIT,
		Fragment = GL_FRAGMENT_SHADER_BIT,
		Compute = GL_COMPUTE_SHADER_BIT,
		All = GL_ALL_SHADER_BITS
	};

	ProgramPipeline() =default;
	~ProgramPipeline();
	
	virtual void init() override;
	
	virtual void cleanup() override;
	
	/**
	 * Sets the specified shader stages of the pipeline to the ones attached to program.
	 * @param program Program from which to retrieved the programable stages.
	 * @param stageBits Shader stages to modify.
	 */
	void useProgramStages(const Program& program, Stage stageBits = Stage::All) const;
	
	/**
	 * Sets the specified shader stages as not configured.
	 * @param stageBits Combinaison of Stages to "clear".
	 */
	void clearProgramStages(Stage stageBits) const;
	
	/**
	 * Binds the ProgramPipeline.
	**/
	void bind() const;

	/**
	 * Unbind any ProgramPipeline currently bound.
	**/
	static void unbind();
};