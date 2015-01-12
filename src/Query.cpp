#include <Query.hpp>

Query::~Query()
{
	cleanup();
}

void Query::init()
{
	glGenQueries(1, &_handle);
}

void Query::cleanup()
{
	glDeleteQueries(1, &_handle);
}

void Query::begin(Target target)
{
	assert(target != Target::Timestamp && target != Target::None);
	_target = target;
	glBeginQuery(to_underlying(target), _handle);
}

void Query::end() const
{
	assert(_target != Target::Timestamp && _target != Target::None);
	glEndQuery(to_underlying(_target));
}
	
void Query::begin(Target target, GLuint index)
{
	assert(target != Target::Timestamp && target != Target::None);
	_target = target;
	glBeginQueryIndexed(to_underlying(target), index, _handle);
}

void Query::end(GLuint index) const
{
	assert(_target != Target::Timestamp && _target != Target::None);
	glEndQueryIndexed(to_underlying(_target), index);
}
	
bool Query::isAvailable() const
{
	return get<int>(Parameter::Available) == GL_TRUE;	
}
