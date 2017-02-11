#pragma once

#include <array>

#include <Texture.hpp>
#include <CubeMap.hpp>

/** @file
 * Set of free functions (overloads) wrapping OpenGL calls of glUniform** and glProgramUniform**
**/

void setUniform(GLint program, GLuint location, const float& value);
void setUniform(GLint program, GLuint location, const int& value);
void setUniform(GLint program, GLuint location, const std::array<int, 2>& value);
void setUniform(GLint program, GLuint location, const std::array<int, 3>& value);
void setUniform(GLint program, GLuint location, const std::array<int, 4>& value);
void setUniform(GLint program, GLuint location, const unsigned int& value);
void setUniform(GLint program, GLuint location, const long long unsigned int& value);
//void setUniform(GLint program, GLuint location, const size_t& value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 2>& value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 3>& value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 4>& value);

void setUniform(GLint program, GLuint location, const float* value);
void setUniform(GLint program, GLuint location, const int* value);
void setUniform(GLint program, GLuint location, const std::array<int, 2>* value);
void setUniform(GLint program, GLuint location, const std::array<int, 3>* value);
void setUniform(GLint program, GLuint location, const std::array<int, 4>* value);
void setUniform(GLint program, GLuint location, const unsigned int* value);
void setUniform(GLint program, GLuint location, const long long unsigned int* value);
//void setUniform(GLint program, GLuint location, const size_t* value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 2>* value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 3>* value);
void setUniform(GLint program, GLuint location, const std::array<unsigned int, 4>* value);

void setUniform(GLuint location, const float& value);
void setUniform(GLuint location, const int& value);
void setUniform(GLuint location, const std::array<int, 2>& value);
void setUniform(GLuint location, const std::array<int, 3>& value);
void setUniform(GLuint location, const std::array<int, 4>& value);
void setUniform(GLuint location, const unsigned int& value);
void setUniform(GLuint location, const long long  unsigned int& value);
void setUniform(GLuint location, const std::array<unsigned int, 2>& value);
void setUniform(GLuint location, const std::array<unsigned int, 3>& value);
void setUniform(GLuint location, const std::array<unsigned int, 4>& value);

void setUniform(GLuint location, const float* value);
void setUniform(GLuint location, const int* value);
void setUniform(GLuint location, const std::array<int, 2>* value);
void setUniform(GLuint location, const std::array<int, 3>* value);
void setUniform(GLuint location, const std::array<int, 4>* value);
void setUniform(GLuint location, const unsigned int* value);
void setUniform(GLuint location, const long long unsigned int* value);
void setUniform(GLuint location, const std::array<unsigned int, 2>* value);
void setUniform(GLuint location, const std::array<unsigned int, 3>* value);
void setUniform(GLuint location, const std::array<unsigned int, 4>* value);
