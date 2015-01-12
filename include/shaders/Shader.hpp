#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#define GLEW_STATIC
#include <GL/glew.h>

#include <OpenGLObject.hpp>

/**
 * Base class for all types of shaders.
 * @todo Add a way to set the source without a file.
**/
class Shader : public OpenGLObject
{
public:
	/**
	 * Default constructor.
	 */
	Shader() =default;
	
	/**
	 *  Destructor.
	 */
	virtual ~Shader();
	
	virtual void init() override;
	
	virtual void cleanup() override;
	
	/**
	 * Loads the source for this shader from the file at path.
	 * @param path Path to the file containing the source for the shader.
	 */
	void loadFromFile(const std::string& path);
	
	/**
	 * Reloads shader from file.
	 * (Should be used only after a successfull call to loadFromFile).
	 * @see loadFromFile
	**/
	void reload();

	/**
	 * Compiles this shader.
	 * Source for the shader must have been set before.
	 */
	void compile();
	
	/**
	 * @return True if properly initialized and compiled, false otherwise.
	**/
	inline bool isValid() const override;
	
protected:
	std::string			_srcPath = "";		///< Path to the last file read by loadFromFile
	bool				_compiled = false;	///< Says if the shader have already been successfully compiled.
	
	/**
	 * @return Type of the managed shader.
	 */
	virtual GLenum getType() const =0;
};

inline bool Shader::isValid() const 
{
	return OpenGLObject::isValid() && _compiled;
}
