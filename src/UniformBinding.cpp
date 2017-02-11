#include <UniformBinding.hpp>

//////////////////////////////////////////////////////////////////
// With Program

void setUniform(GLint program, GLuint location, const float& value)
{
	glProgramUniform1f(program, location, value);
}

void setUniform(GLint program, GLuint location, const int& value)
{
	glProgramUniform1i(program, location, value);
}

void setUniform(GLint program, GLuint location, const std::array<int, 2>& value)
{
	glProgramUniform2iv(program, location, 1, (const GLint*) value.data());
}

void setUniform(GLint program, GLuint location, const std::array<int, 3>& value)
{
	glProgramUniform3iv(program, location, 1, (const GLint*) value.data());
}

void setUniform(GLint program, GLuint location, const std::array<int, 4>& value)
{
	glProgramUniform4iv(program, location, 1, (const GLint*) value.data());
}

void setUniform(GLint program, GLuint location, const unsigned int& value)
{
	glProgramUniform1ui(program, location, value);
}

void setUniform(GLint program, GLuint location, const long long unsigned int& value)
{
	glProgramUniform1ui(program, location, value);
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 2>& value)
{
	glProgramUniform2uiv(program, location, 1, (const GLuint*) value.data());
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 3>& value)
{
	glProgramUniform3uiv(program, location, 1, (const GLuint*) value.data());
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 4>& value)
{
	glProgramUniform4uiv(program, location, 1, (const GLuint*) value.data());
}

///////////////////////////////////////////////////////////////////
// Pointers

void setUniform(GLint program, GLuint location, const float* value)
{
	glProgramUniform1f(program, location, *value);
}

void setUniform(GLint program, GLuint location, const int* value)
{
	glProgramUniform1i(program, location, *value);
}

void setUniform(GLint program, GLuint location, const std::array<int, 2>* value)
{
	glProgramUniform2iv(program, location, 1, (const GLint*) (*value).data());
}

void setUniform(GLint program, GLuint location, const std::array<int, 3>* value)
{
	glProgramUniform3iv(program, location, 1, (const GLint*) (*value).data());
}

void setUniform(GLint program, GLuint location, const std::array<int, 4>* value)
{
	glProgramUniform4iv(program, location, 1, (const GLint*) (*value).data());
}

void setUniform(GLint program, GLuint location, const unsigned int* value)
{
	glProgramUniform1ui(program, location, *value);
}

void setUniform(GLint program, GLuint location, const long long unsigned int* value)
{
	glProgramUniform1ui(program, location, *value);
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 2>* value)
{
	glProgramUniform2uiv(program, location, 1, (const GLuint*) (*value).data());
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 3>* value)
{
	glProgramUniform3uiv(program, location, 1, (const GLuint*) (*value).data());
}

void setUniform(GLint program, GLuint location, const std::array<unsigned int, 4>* value)
{
	glProgramUniform4uiv(program, location, 1, (const GLuint*) (*value).data());
}

///////////////////////////////////////////////////////////////////
// Non-Program stuff

void setUniform(GLuint location, const float& value)
{
	glUniform1f(location, value);
}

void setUniform(GLuint location, const int& value)
{
	glUniform1i(location, value);
}

void setUniform(GLuint location, const std::array<int, 2>& value)
{
	glUniform2iv(location, 1, (const GLint*) value.data());
}

void setUniform(GLuint location, const std::array<int, 3>& value)
{
	glUniform3iv(location, 1, (const GLint*) value.data());
}

void setUniform(GLuint location, const std::array<int, 4>& value)
{
	glUniform4iv(location, 1, (const GLint*) value.data());
}

void setUniform(GLuint location, const unsigned int& value)
{
	glUniform1ui(location, value);
}

void setUniform(GLuint location, const long long unsigned int& value)
{
	glUniform1ui(location, value);
}

void setUniform(GLuint location, const std::array<unsigned int, 2>& value)
{
	glUniform2uiv(location, 1, (const GLuint*) value.data());
}

void setUniform(GLuint location, const std::array<unsigned int, 3>& value)
{
	glUniform3uiv(location, 1, (const GLuint*) value.data());
}

void setUniform(GLuint location, const std::array<unsigned int, 4>& value)
{
	glUniform4uiv(location, 1, (const GLuint*) value.data());
}

///////////////////////////////////////////////////////////////////
// Pointers 

void setUniform(GLuint location, const float* value)
{
	glUniform1f(location, *value);
}

void setUniform(GLuint location, const int* value)
{
	glUniform1i(location, *value);
}

void setUniform(GLuint location, const std::array<int, 2>*value )
{
	glUniform2iv(location, 1, (const GLint*) (*value).data());
}

void setUniform(GLuint location, const std::array<int, 3>*value )
{
	glUniform3iv(location, 1, (const GLint*) (*value).data());
}

void setUniform(GLuint location, const std::array<int, 4>*value )
{
	glUniform4iv(location, 1, (const GLint*) (*value).data());
}

void setUniform(GLuint location, const unsigned int* value )
{
	glUniform1ui(location, *value);
}

void setUniform(GLuint location, const long long unsigned int* value )
{
	glUniform1ui(location, *value);
}

void setUniform(GLuint location, const std::array<unsigned int, 2>* value)
{
	glUniform2uiv(location, 1, (const GLuint*) (*value).data());
}

void setUniform(GLuint location, const std::array<unsigned int, 3>* value)
{
	glUniform3uiv(location, 1, (const GLuint*) (*value).data());
}

void setUniform(GLuint location, const std::array<unsigned int, 4>* value)
{
	glUniform4uiv(location, 1, (const GLuint*) (*value).data());
}
