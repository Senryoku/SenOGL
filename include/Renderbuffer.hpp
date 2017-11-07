#pragma once

#include <cassert>

#include <OpenGLObject.hpp>
#include <Enums.hpp>

/**
 * Renderbuffer Object
**/
class Renderbuffer : public OpenGLObject
{
public:
	/**
	 * Destructor
	**/
	virtual ~Renderbuffer();
	
	/**
	 * Initialization of the OpenGL object
	**/
	virtual void init() override; 
	
	/**
	 * Destroys the OpenGLObject.
	**/ 
	virtual void cleanup() override;
	
	void bind() const;
	
	/**
	 * Initialize a default Renderbuffer, matching the behavior of Texture2D::create
	 * Mainly used by Framebuffer.
	 * @see Texture::create
	 * @see Framebuffer::init
	 */
	void create(GLsizei width, GLsizei height, GLenum internalFormat);

	void storage(GLenum internalFormat, GLsizei width, GLsizei height, GLsizei samples = 0);
	
	inline bool isValid() const override;
	
private:
	bool	_initialized = false; ///< True if the renderbuffer is fully initialized.
};

bool Renderbuffer::isValid() const
{
	return OpenGLObject::isValid() && _initialized;
}
