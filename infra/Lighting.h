#pragma once

#include <glErrors.h>
#include <Shader.h>
#include <GL/glew.h>

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Lighting {
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Color;

		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

	public:

		Lighting(glm::vec3 Position,glm::vec3 Color);
		~Lighting();
		
		void OnUpdatePos(glm::vec3 pos_or_speed,bool is_pos=false);
		void OnUpdateColor(glm::vec3 Color);

		void OnUpdateAmbient(glm::vec3 ambient);
		void OnUpdateDiffuse(glm::vec3 diffuse);
		void OnUpdateSpecular(glm::vec3 specular);

		void OnUpdateShader(std::vector<Shader*>& shaders);
		void OnImGuiRender();
};



