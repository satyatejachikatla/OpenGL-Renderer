#pragma once

#include <glErrors.h>
#include <Shader.h>
#include <GL/glew.h>

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {

	public:
		Light(){}
		~Light(){}

		virtual void OnRender(std::vector<Shader*>& shaders){}
		virtual void OnImGuiRender(){}
};

class LightList : Light{

	private:
		std::vector<std::shared_ptr<Light>> m_Lights;

	public:

		LightList();
		~LightList();

		void OnRender(std::vector<Shader*>& shaders);
		void OnImGuiRender();
};

class PointLight : Light{
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Color;

		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

	public:

		PointLight(glm::vec3 Position,glm::vec3 Color);
		~PointLight();
		
		void OnUpdatePos(glm::vec3 pos_or_speed,bool is_pos=false);
		void OnUpdateColor(glm::vec3 Color);

		void OnUpdateAmbient(glm::vec3 ambient);
		void OnUpdateDiffuse(glm::vec3 diffuse);
		void OnUpdateSpecular(glm::vec3 specular);

		virtual void OnRender(std::vector<Shader*>& shaders);
		virtual void OnImGuiRender();
};
