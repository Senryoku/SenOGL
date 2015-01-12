#include <Sampler.hpp>

Sampler::Sampler(GLuint handle) : 
	OpenGLObject(handle)
{
	if(!isSampler(handle))
		std::cerr << "Error constructing Sampler: Provided OpenGL name isn't a Sampler name." << std::endl;
}
	
Sampler::~Sampler()
{
	cleanup();
}

void Sampler::bind(unsigned int unit) const 
{
	glBindSampler(unit, _handle);
}

void Sampler::cleanup()
{
	glDeleteSamplers(1, &_handle);
}
