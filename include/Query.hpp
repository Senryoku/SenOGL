#pragma once

#include <cassert>

#include <OpenGLObject.hpp>
#include <Enums.hpp>

/**
 * Query Object
 * @todo A lot.
**/
class Query : public OpenGLObject
{
public:
	enum class Target : GLenum
	{
		SamplesPassed = GL_SAMPLES_PASSED,
		AnySamplesPassed = GL_ANY_SAMPLES_PASSED,
		AnySamplesPassedConservative = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
		PrimitivesGenerated = GL_PRIMITIVES_GENERATED,
		TransformFeedbackPrimitivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
		TimeElapsed = GL_TIME_ELAPSED,
		Timestamp = GL_TIMESTAMP,
		None
	};
	
	enum class Parameter : GLenum
	{
		Result = GL_QUERY_RESULT,
		ResultNoWait = GL_QUERY_RESULT_NO_WAIT,
		Available = GL_QUERY_RESULT_AVAILABLE
	};

	/**
	 * Destructor
	**/
	virtual ~Query();
	
	/**
	 * Initialization of the OpenGL object
	**/
	virtual void init() override; 
	
	/**
	 * Destroys the OpenGLObject.
	**/ 
	virtual void cleanup() override;
	
	void begin(Target target);
	
	void end() const;
	
	void begin(Target target, GLuint index);
	
	void end(GLuint index) const;
	
	template<typename T>
	T get(Parameter param) const;
	
	template<typename T>
	T get() const;
	
	template<typename T>
	T getNoWait() const;
	
	template<typename T>
	T getCounter() const;
	
	bool isAvailable() const;

private:
	Target	_target = Target::None;	///< Target of the last begun query.
};

inline void getQueryObject(GLuint id, GLenum pname, GLint* params)
{
	glGetQueryObjectiv(id, pname, params);
}

inline void getQueryObject(GLuint id, GLenum pname, GLuint* params)
{
	glGetQueryObjectuiv(id, pname, params);
}

inline void getQueryObject(GLuint id, GLenum pname, GLint64* params)
{
	glGetQueryObjecti64v(id, pname, params);
}

inline void getQueryObject(GLuint id, GLenum pname, GLuint64* params)
{
	glGetQueryObjectui64v(id, pname, params);
}

template<typename T>
T Query::get(Parameter param) const
{
	T ret = 0;
	getQueryObject(_handle, to_underlying(param), &ret);
	return ret;	
}
	
template<typename T>
T Query::get() const
{
	return get<T>(Parameter::Result);
}

template<typename T>
T Query::getNoWait() const
{
	return get<T>(Parameter::ResultNoWait);
}

template<typename T>
T Query::getCounter() const
{
	assert(_target == Target::None || _target == Target::TimeElapsed);
	glQueryCounter(_handle, to_underlying(Target::Timestamp));
	return get<T>(Parameter::Result);
}