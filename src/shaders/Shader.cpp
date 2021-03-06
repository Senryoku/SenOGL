#include "Shader.hpp"

#include <sstream>

#include <Context.hpp>

Shader::~Shader()
{
	cleanup();
}

void Shader::init()
{
	if(_handle != 0)
		return;
		
	Context::safeCheck(
		[&]() {
			_handle = glCreateShader(getType());
		},
		"glCreateShader"
	);
	if(_handle == 0 || !isShader(_handle))
	{
		std::cerr << __PRETTY_FUNCTION__ << " : Error glCreateShader(), "
			<< "\n\t_handle : " << _handle
			<< "\n\tisShader(_handle) : " << isShader(_handle)
			<< std::endl;
	}
	
	_compiled = false;
}

void Shader::cleanup()
{
	if(_handle)
		glDeleteShader(_handle);
}

void Shader::processFile(const std::string& path, GLchar** cSrc, GLint* lengths, size_t& l)
{
	std::ifstream Src(path);
	if(!Src.good())
	{
		std::cerr << __PRETTY_FUNCTION__ << " : Error opening shader " << path << std::endl;
		return;
	}
	
	while(Src.good()) 
	{
		cSrc[l] = new GLchar[1024];
		Src.getline(cSrc[l], 1024);
		
		// Preprocessing
		if(cSrc[l][0] == '#')
		{
			std::stringstream ss(cSrc[l]);
			std::string str;
			ss >> str;
			if(str == "#pragma")
			{
				GLchar* tmp = cSrc[l];
				bool pass = true;
				ss >> str; // Extract special instruction
				if(str == "include")
				{
					ss >> str; // Get file path
					auto pos = path.find_last_of('/');
					if(pos == std::string::npos)
						pos = path.find_last_of('\\');
					std::string inclPath = path.substr(0, pos + 1);
					inclPath.append(str);
					processFile(inclPath, cSrc, lengths, l);
				} else pass = false;
				
				if(pass) // Already processed: Ignore this line
				{
					delete[] tmp;
					continue;
				} else { // Restore it otherwise.
					cSrc[l] = tmp;
				}
			}
		} 
		
		lengths[l] = Src.gcount();
		if(lengths[l] > 0)
		{
			cSrc[l][lengths[l] - 1] = '\n';
			cSrc[l][lengths[l]] = '\0';
			++l;
		} else delete[] cSrc[l];
	}
	Src.close();
}

void Shader::loadFromFile(const std::string& path)
{
	init();

	GLint lengths[1024];
	GLchar* cSrc[1024];
	size_t l = 0;

	processFile(path, cSrc, lengths, l);

	Context::safeCheck(
		[&]() {
			glShaderSource(_handle, l, (const GLchar**) cSrc, lengths);
		},
		"glShaderSource on \"" + path + "\""
	);
	for(size_t i = 0; i < l; ++i)
		delete cSrc[i];
		
	_srcPath = path;
	//std::cout << "... Done. " << std::endl;
}
	
void Shader::setSource(const std::string& source)
{
	const GLchar* src[1] = {source.c_str()};
	Context::safeCheck(
		[&]() {
			glShaderSource(_handle, 1, src, NULL);
		},
		"glShaderSource"
	);
}

void Shader::reload()
{
	assert(!_srcPath.empty());
	if(_srcPath.empty())
		return;
	loadFromFile(_srcPath);
}

void Shader::compile()
{
	assert(_handle != 0);
    glCompileShader(_handle);
	
	// Check results
    int rvalue;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &rvalue);
    if (!rvalue)
	{
        std::cerr << __PRETTY_FUNCTION__ << " : Error while compiling shader " << _srcPath << std::endl;
        GLchar log[10240];
        GLsizei length;
        glGetShaderInfoLog(_handle, 10239, &length, log);
        std::cerr << "Compiler log " << log << std::endl;
		_compiled = false;
    } else {
		_compiled = true;
	}
}
