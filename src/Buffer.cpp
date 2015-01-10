#include <Buffer.hpp>

#include <cassert>

Buffer::Buffer(Type type, GLuint handle) : 
	OpenGLObject(handle),
	_type(type)
{
}
	
Buffer::~Buffer()
{
	cleanup();
}

void Buffer::cleanup()
{
	glDeleteBuffers(1, &_handle);
	_handle = 0;
}

void Buffer::bind() const
{
	assert(isValid());
    glBindBuffer(to_underlying(_type), getName());
}

void Buffer::bind(Type t) const
{
	assert(isValid());
    glBindBuffer(to_underlying(t), getName());
}

void Buffer::bind(GLuint bindingPoint, GLintptr offset, GLsizeiptr size) const
{
	assert(_type == Type::AtomicCounter || _type == Type::TransformFeedback || 
		   _type == Type::Uniform || _type == Type::ShaderStorage);
	// Default values for offset and size: use entire buffer.
	if(offset == 0 && size == 0)
	{
		glBindBufferBase(to_underlying(_type), bindingPoint, getName());
	} else {
		glBindBufferRange(to_underlying(_type), bindingPoint, getName(), offset, size);
	}
}
	
void Buffer::bind(Type target, GLuint bindingPoint, GLintptr offset, GLsizeiptr size) const
{
	assert(target == AtomicCounter || target == TransformFeedback || target == Uniform || target == ShaderStorage);
	// Default values for offset and size: use entire buffer.
	if(offset == 0 && size == 0)
	{
		glBindBufferBase(to_underlying(target), bindingPoint, getName());
	} else {
		glBindBufferRange(to_underlying(target), bindingPoint, getName(), offset, size);
	}
}
	
void Buffer::unbind() const
{
    glBindBuffer(to_underlying(_type), 0);
}

void Buffer::init()
{
	if(_handle != 0)
		cleanup();
	glGenBuffers(1, &_handle);
}

void Buffer::init(Type t)
{
	setType(t);
	init();
}

void Buffer::data(const void* data, size_t size, Buffer::Usage usage) const
{
	bind();
    glBufferData(to_underlying(_type), size, data, to_underlying(usage));
}

void Buffer::store(const void* data, size_t size, Buffer::StorageUsage flags) const
{
	bind();
    glBufferStorage(to_underlying(_type), size, data, to_underlying(flags));
}

void Buffer::subData(size_t offset, size_t size, const void* data) const
{
	bind();
	glBufferSubData(to_underlying(_type), offset, size, data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// IndexedBuffer

IndexedBuffer::IndexedBuffer(Type type) : 
	Buffer(type)
{
	assert(_type == Type::AtomicCounter || _type == Type::TransformFeedback || 
		   _type == Type::Uniform || _type == Type::ShaderStorage);
}
	
void IndexedBuffer::bind(GLuint bindingPoint)
{
	Buffer::bind(bindingPoint);
	_bindingPoint = bindingPoint;
	_bound = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// UniformBuffer

UniformBuffer::UniformBuffer() : 
	IndexedBuffer(Type::Uniform)
{
}
