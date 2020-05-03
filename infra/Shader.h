#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>

#include <glErrors.h>

struct ShaderProgrameSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {

	private:
		static std::vector<unsigned int> TotalRendererIDList_;

		unsigned int m_RendererID;
		bool m_LoadFailedFlag;

		std::string m_FilePath;
		mutable std::unordered_map<std::string,int> m_UniformLocationCache;  

		ShaderProgrameSource ParseShader(const std::string filePath);
		unsigned int CompileShader(unsigned int type,const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader );

		unsigned int GetUniformLocation(const std::string& name) const;
		

	public:
		static const std::vector<unsigned int>& TotalRendererIDList() { return TotalRendererIDList_; }

		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		bool isLoadFailed() const;

		// Set Uniforms //
		void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
		void SetUniform1f(const std::string& name,float value);
		void SetUniform1i(const std::string& name,int value);
		void SetUniformMat4f(const std::string& name,const glm::mat4& matrix);
		void SetUniform1iv(const std::string& name,unsigned int count ,const int* data);
		void SetUniformVec2f(const std::string& name,const glm::vec2& data);
		void SetUniformVec3f(const std::string& name,const glm::vec3& data);

};


