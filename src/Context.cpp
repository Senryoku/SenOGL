#include <Context.hpp>

namespace Context
{
	
void APIENTRY debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	(void)source; (void)type; (void)id; 
	(void)severity; (void)length; (void)userParam;
	std::cerr << message << std::endl;
	if(severity == GL_DEBUG_SEVERITY_HIGH)
	{
		std::cerr << "Severe OpenGL error, aborting..." << std::endl;
		abort();
	}
}

};
