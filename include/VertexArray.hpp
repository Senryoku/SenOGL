#pragma once

#include <OpenGLObject.hpp>
#include <Buffer.hpp>

/**
 * Vertex Array Object (VAO)
 *
**/
class VertexArray : public OpenGLObject
{
public:
	/**
	 * Destructor
	**/
	virtual ~VertexArray();
	
	/**
	 * Initialization of the OpenGL object
	**/
	virtual void init() override; 
	
	/**
	 * Destroys the OpenGLObject.
	**/ 
	virtual void cleanup() override;
	
	/**
	 * Binds the VAO.
	**/
	void bind() const;

	/**
	 * Unbind any VAO currently bound.
	**/
	static void unbind();
	
	/**
	 * glVertexAttribPointer
	**/
	void attribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;
	
	/**
	 * glVertexAttribPointerI
	**/
	void attributeI(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) const;
private:
};
