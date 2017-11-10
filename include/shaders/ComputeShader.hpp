#pragma once

#include <Shader.hpp>
#include <Enums.hpp>

class Program;

/**
 * Compute Shader.
 * This type of shader can hold a program and be used alone.
 * @see Shader
 * @see Program
**/
class ComputeShader : public Shader
{
public:
	/**
	 * Barrier Bits.
	 * @see https://www.khronos.org/opengles/sdk/docs/man31/html/glMemoryBarrier.xhtml
	 */
	enum class BarrierBit : GLbitfield
	{
		VertexAttribArray   = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
		ElementArrayBarrier = GL_ELEMENT_ARRAY_BARRIER_BIT,
		Uniform             = GL_UNIFORM_BARRIER_BIT,
		TextureFetch        = GL_TEXTURE_FETCH_BARRIER_BIT,
		ShaderImageAccess   = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
		Commande            = GL_COMMAND_BARRIER_BIT,
		PixelBuffer         = GL_PIXEL_BUFFER_BARRIER_BIT,
		TextureUpdate       = GL_TEXTURE_UPDATE_BARRIER_BIT,
		BufferUpdate        = GL_BUFFER_UPDATE_BARRIER_BIT,
		Framebuffer         = GL_FRAMEBUFFER_BARRIER_BIT,
		TransformFeedback   = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
		AtomicCounter       = GL_ATOMIC_COUNTER_BARRIER_BIT,
		ShaderStorage       = GL_SHADER_STORAGE_BARRIER_BIT,
		All                 = GL_ALL_BARRIER_BITS
	};

	/// Structure containing size information about Compute shader workgroups
	struct WorkgroupSize
	{
		int x = 0, ///< X Size
			y = 0, ///< Y Size
			z = 0; ///< Z Size
	};

	/**
	 * Default constructor
	 * @param standalone If true, attach the shader to a new dedicated program.
	**/
	ComputeShader(bool standalone = true);
	
	ComputeShader(const std::string& file, bool standalone = true);
	
	/**
	 * Destructor
	**/
	~ComputeShader();
	
	/**
	 * Compiles and, if set as standalone, links the associated Program.
	 * @see Shader::compile()
	**/
	void compile();
	
	/**
	 * Use the associated Program.
	 * @see Program::use()
	**/
	void use() const;
	
	/**
	 * Starts the execution of the compute shader
	 * @param x Number of workgroups to start on the x 'axis'
	 * @param y Number of workgroups to start on the y 'axis'
	 * @param z Number of workgroups to start on the z 'axis'
	**/
	inline void compute(GLint x, GLint y = 1, GLint z = 1) const;
	
	/**
	 * @return Associated Program
	 * @see Program
	**/
	inline Program& getProgram();
	
	/**
	 * @return Associated Program
	 * @see Program
	**/
	inline const Program& getProgram() const;
	
	/**
	 * Note: Shader must be compiled and associated to a linked Program.
	 * @return Workgroup sizes as specified in the compute shader.
	 * @see compile()
	 * @see Program
	**/
	const WorkgroupSize& getWorkgroupSize();
	
	// Static functions
	
	/**
	 * @param BF Bitwise combinaison of any BarrierBit, or BarrierBit::All.
	 * @see glMemoryBarrier
	**/
	inline static void memoryBarrier(BarrierBit BF = BarrierBit::All); 
	
	/**
	 * @param BF Must be a combinaison of BarrierBit::AtomicCounter, BarrierBit::Framebuffer, BarrierBit::ShaderImageAccess
		BarrierBit::ShaderStorage, BarrierBit::TextureFetch and BarrierBit::UniformBarrier. Or BarrierBit::All.
	 * @see glMemoryBarrier
	**/
	inline static void memoryBarrierByRegion(BarrierBit BF = BarrierBit::All); 
	
	/**
	 * Starts the execution of the curently 'bound' compute shader
	 * @param x Number of workgroups to start on the x 'axis'
	 * @param y Number of workgroups to start on the y 'axis'
	 * @param z Number of workgroups to start on the z 'axis'
	**/
	inline static void dispatchCompute(GLint x, GLint y = 1, GLint z = 1);
	
private:
	bool 			_standalone = true;	///< True if owns a dedicated program.
	Program*		_program = nullptr;	///< Associated program.
	WorkgroupSize	_workgroupSize;		///< Workgroup Size.
	
	inline virtual GLenum getType() const override;
	
	void initProgram();
	
	friend class Program;
};

// Inline functions declarations

inline Program& ComputeShader::getProgram()
{
	assert(_program != nullptr);
	return *_program;
}

inline const Program& ComputeShader::getProgram() const
{
	assert(_program != nullptr);
	return *_program;
}
	
inline void ComputeShader::compute(GLint x, GLint y, GLint z) const
{
	if(_standalone) use();
	dispatchCompute(x, y, z);
}

inline GLenum ComputeShader::getType() const 
{
	return GL_COMPUTE_SHADER;
}
	
// Static functions

inline void ComputeShader::memoryBarrier(BarrierBit BF)
{
	glMemoryBarrier(to_underlying(BF));
} 

inline void ComputeShader::memoryBarrierByRegion(BarrierBit BF)
{
	glMemoryBarrierByRegion(to_underlying(BF));
} 

inline void ComputeShader::dispatchCompute(GLint x, GLint y, GLint z)
{
	glDispatchCompute(x, y, z);
}