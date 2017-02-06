#include <Buffer.hpp>

#include <cassert>

#include <Context.hpp>

Buffer::Buffer(Target type, GLuint handle) : 
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
	if(_handle)
	{
		glDeleteBuffers(1, &_handle);
		_handle = 0;
	}
}

void Buffer::bind() const
{
	assert(isValid());
    glBindBuffer(to_underlying(_type), getName());
}

void Buffer::bind(Target t) const
{
	assert(isValid());
    glBindBuffer(to_underlying(t), getName());
}

void Buffer::bind(GLuint bindingPoint, GLintptr offset, GLsizeiptr size) const
{
	assert(_type == Target::AtomicCounter || _type == Target::TransformFeedback || 
		   _type == Target::Uniform || _type == Target::ShaderStorage);
	// Default values for offset and size: use entire buffer.
	if(offset == 0 && size == 0)
	{
		glBindBufferBase(to_underlying(_type), bindingPoint, getName());
	} else {
		glBindBufferRange(to_underlying(_type), bindingPoint, getName(), offset, size);
	}
}
	
void Buffer::bind(Target target, GLuint bindingPoint, GLintptr offset, GLsizeiptr size) const
{
	assert(target == Target::AtomicCounter || target == Target::TransformFeedback || 
		   target == Target::Uniform || target == Target::ShaderStorage);
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
	
	Context::safeCheck(
		[&]() {
			glGenBuffers(1, &_handle);
		},
		"glGenBuffers"
	);
	
	assert(isValid());
}

void Buffer::init(Target t)
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

IndexedBuffer::IndexedBuffer(Target type) : 
	Buffer(type)
{
	assert(_type == Target::AtomicCounter || _type == Target::TransformFeedback || 
		   _type == Target::Uniform || _type == Target::ShaderStorage);
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
	IndexedBuffer(Target::Uniform)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ShaderStorage

ShaderStorage::ShaderStorage() : 
	IndexedBuffer(Target::ShaderStorage)
{
}
