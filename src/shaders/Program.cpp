#include "Program.hpp"

#include <Context.hpp>

Program::Program()
{
}

Program::~Program()
{
	cleanup();
}

void Program::init()
{
	if(_handle != 0)
		cleanup();
		
	Context::safeCheck(
		[&]() {
			_handle = glCreateProgram();
		},
		"glCreateProgram"
	);
	if(_handle == 0)
		std::cerr << __PRETTY_FUNCTION__ << " : Error glCreateProgram()" << std::endl;
}

void Program::cleanup()
{
	glDeleteProgram(_handle);
	_handle = 0;
}

void Program::attachShader(GLuint shaderName)
{
	if(_handle == 0)
		init();
	assert(Shader::isShader(shaderName));
	if(!Shader::isShader(shaderName)) 
		std::cerr << __PRETTY_FUNCTION__ << ": Tried to attach something that isn't a shader to a program!" << std::endl;
    glAttachShader(_handle, shaderName);
	Context::checkError("glAttachShader");
}

void Program::attach(const Shader& shader)
{
	if(_handle == 0)
		init();
	if(!Shader::isShader(shader.getName())) 
	{
		std::cerr << __PRETTY_FUNCTION__ << ": Shader ";
		if(shader.getPath() != "")
			std::cerr << "(loaded from " << shader.getPath() << ") ";
		std::cerr << "is invalid and can't be attach to a program." << std::endl;
	} else {
		glAttachShader(_handle, shader.getName());
		Context::checkError("glAttachShader");
	}
}

void Program::attach(ComputeShader& cshader)
{
	attachShader(static_cast<const Shader&>(cshader));
	cshader._program = this;
}

void Program::link()
{
	assert(_handle != 0);
	
	int rvalue;
    glLinkProgram(_handle);
	Context::checkError("glLinkProgram");
    glGetProgramiv(_handle, GL_LINK_STATUS, &rvalue);
    if (!rvalue)
	{
        std::cerr << __FUNCTION__ << " : Error in linking shader program." << std::endl;
        GLchar log[10240];
        GLsizei length;
        glGetProgramInfoLog(_handle, 10239, &length, log);
        std::cerr << "Linker log: " << log << std::endl;
		
		_linked = false;
    } else {
		_linked = true;
	}
}

void Program::use() const
{
	assert(isValid());
    glUseProgram(_handle);
}

GLint Program::getUniformLocation(const std::string& name) const
{
	assert(isValid());
	return glGetUniformLocation(getName(), name.c_str());
}

GLuint Program::getResourceIndex(GLenum interface, const std::string& name) const
{
	assert(isValid());
	return glGetProgramResourceIndex(getName(), interface, name.c_str());
}

GLuint Program::getUniformBlockIndex(const std::string& name) const
{
	assert(isValid());
	GLuint r = glGetUniformBlockIndex(getName(), name.c_str());
	if(r == GL_INVALID_INDEX) std::cerr << "Warning: Invalid Uniform Block name " << name << std::endl;
	assert(r != GL_INVALID_INDEX);
	return r;
}
	
void Program::bindUniformBlock(GLuint uniformBlockIndex, GLuint uniformBlockBindingPoint) const
{
	assert(isValid());
	assert(uniformBlockBindingPoint < GL_MAX_UNIFORM_BUFFER_BINDINGS);
	glUniformBlockBinding(getName(), uniformBlockIndex, uniformBlockBindingPoint);
}
	
void Program::bindUniformBlock(const std::string& name, GLuint uniformBlockBindingPoint) const
{
	assert(isValid());
	bindUniformBlock(getUniformBlockIndex(name), uniformBlockBindingPoint);
}
	
void Program::bindUniformBlock(const std::string& name, const UniformBuffer& uniformBuffer) const
{
	assert(isValid());
	assert(uniformBuffer.isBound());
	bindUniformBlock(getUniformBlockIndex(name), uniformBuffer.getBindingPoint());
}

void Program::bindShaderStorageBlock(const std::string& name, const ShaderStorage& sso) const
{
	assert(isValid());
	assert(sso.isBound());
	glShaderStorageBlockBinding(_handle, getResourceIndex(GL_SHADER_STORAGE_BLOCK, name), sso.getBindingPoint());
}

void Program::setSubroutine(ShaderType shadertype, const std::string& uniformName, const std::string& functionName)
{
	auto& subroutines = _activeSubroutines[shadertype];
	if(subroutines.empty())
	{
		GLsizei uniformCount;
		glGetProgramStageiv(_handle, to_underlying(shadertype),
				 GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &uniformCount);
				 
		if(uniformCount == 0)
		{
			std::cerr << "No subroutines at this stage for this program.(searching for " 
						<< uniformName << " and " << functionName << ")." << std::endl;
			return;
		}
		
		subroutines.resize(uniformCount, 0);
	}

	GLint uniformLocation = glGetSubroutineUniformLocation(_handle, to_underlying(shadertype), uniformName.c_str());
	if(uniformLocation < 0)
	{
		std::cerr << "Uniform " << uniformName << " not found." << std::endl;
		return;
	}
	
	GLuint r = getSubroutineIndex(shadertype, functionName.c_str());

	if(r == GL_INVALID_INDEX)
	{
		std::cerr << "Subroutine '" << functionName << "' not found." << std::endl;
	} else {
		subroutines[uniformLocation] = r;
		glUniformSubroutinesuiv(to_underlying(shadertype), subroutines.size(), subroutines.data());
	}
}

GLuint Program::getSubroutineIndex(ShaderType shadertype, const std::string& name) const
{
	return glGetSubroutineIndex(_handle, to_underlying(shadertype), name.c_str());
}
	
void Program::useNone()
{
    glUseProgram(0);
}
