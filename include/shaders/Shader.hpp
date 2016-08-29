#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

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
	
	Shader(const Shader&) =delete;
	
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
	 * Set the source of the shader (replacing any previous loaded source).
	 * @param source String source.
	 */
	void setSource(const std::string& source);
	
	/**
	 * Reloads shader from file.
	 * (Should be used only after a successful call to loadFromFile).
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
	
	/**
	 * @return Path to the source code (if loaded from a file).
	**/
	inline const std::string& getPath() const { return _srcPath; }
	
	/**
	 * @see glIsShader
	**/
	inline static bool isShader(GLuint name) { return glIsShader(name) == GL_TRUE; }
	
protected:
	std::string		_srcPath = "";		///< Path to the last file read by loadFromFile
	bool			_compiled = false;	///< Says if the shader have already been successfully compiled.
	
	/**
	 * @return Type of the managed shader.
	 */
	virtual GLenum getType() const =0;
	
	/**
	 * Internaly used to load shaders from files.
	 * @param path Path to the file
	 * @param cSrc Array of strings to populate with the source.
	 * @param lengths Array of lengths to populate from the source.
	 * @param l Current line.
	**/
	void processFile(const std::string& path, GLchar** cSrc, GLint* lengths, size_t& l);
};

inline bool Shader::isValid() const 
{
	return OpenGLObject::isValid() && _compiled;
}
