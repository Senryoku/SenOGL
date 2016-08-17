#include <ProgramPipeline.hpp>

#include <Context.hpp>

ProgramPipeline::~ProgramPipeline()
{
	cleanup();
}

void ProgramPipeline::init()
{
	cleanup();
	
	Context::safeCheck(
		[&]() {
			glGenProgramPipelines(1, &_handle);
		},
		"glGenProgramPipelines"
	);
}

void ProgramPipeline::cleanup()
{
	if(_handle)
	{
		glDeleteProgramPipelines(1, &_handle);
		_handle = 0;
	}
}

void ProgramPipeline::useProgramStages(const Program& program, Stage stageBits) const
{
	glUseProgramStages(getName(), to_underlying(stageBits), program.getName());
}

void ProgramPipeline::clearProgramStages(Stage stageBits) const
{
	glUseProgramStages(getName(), to_underlying(stageBits), 0);
}

void ProgramPipeline::bind() const
{
	glBindProgramPipeline(_handle);
}

void ProgramPipeline::unbind()
{
	glBindProgramPipeline(0);
}
