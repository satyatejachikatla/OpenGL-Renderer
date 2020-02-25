#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>
#include "glErrors.h"

struct ShaderProgrameSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {

	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		std::unordered_map<std::string,int> m_UniformLocationCache;  

		ShaderProgrameSource ParseShader(const std::string filePath);
		unsigned int CompileShader(unsigned int type,const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader );

		unsigned int GetUniformLocation(const std::string& name);
		

	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Set Uniforms //
		void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
		void SetUniform1f(const std::string& name,float value);
};

#endif /* __SHADER_H__ */
