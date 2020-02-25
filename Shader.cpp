#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0) {


	ShaderProgrameSource source = ParseShader(filepath);
//	std::cout << "Vertex" << std::endl;
//	std::cout << source.VertexSource << std::endl;
//	std::cout << "Fragment" << std::endl;
//	std::cout << source.FragmentSource << std::endl;


	glCall(m_RendererID=CreateShader(source.VertexSource,source.FragmentSource));
}

Shader::~Shader() {
	glCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
	glCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const {
	glCall(glUseProgram(0));
}

// Set Uniforms //
void Shader::SetUniform1f(const std::string& name,float value) {
	glCall(glUniform1f(GetUniformLocation(name),value));
}
void Shader::SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3) {
	glCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

unsigned int Shader::GetUniformLocation(const std::string& name) {
	/*Setting Data in Shader*/
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	glCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
	if(location == -1) {
		std::cerr << "Warning : uniform "<< name << " dosent exist" << std::endl;
	}
	
	m_UniformLocationCache[name] = location;

	return location;
}


ShaderProgrameSource Shader::ParseShader(const std::string filePath) {

	std::ifstream stream(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};	

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream,line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << "\n"; 
		}
	}

	return {ss[0].str(),ss[1].str()};

}

unsigned int Shader::CompileShader(unsigned int type,const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	/* sharder id , num shaders , source pointer, no array lenths required */
	glCall(glShaderSource(id,1,&src,nullptr));
	glCall(glCompileShader(id));

	int result;
	glCall(glGetShaderiv(id,GL_COMPILE_STATUS,&result));
	if (result == GL_FALSE) {
		int length;
		glCall(glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length));
		char* message = (char *)alloca(length*sizeof(char));\

		glCall(glGetShaderInfoLog(id,length,&length,message));

		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<std::endl;
		std::cerr << message <<std::endl;

		glCall(glDeleteShader(id));
		return 0;

	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader )  {
	glCall(unsigned int program = glCreateProgram());
	glCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	glCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

	glCall(glAttachShader(program,vs));
	glCall(glAttachShader(program,fs));
	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	return program;
}
