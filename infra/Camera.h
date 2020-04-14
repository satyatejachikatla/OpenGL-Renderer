#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Shader.h>

class Camera {
	private:
		static Camera* m_CurrentCam;

		glm::vec3 m_CameraPos;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraTarget;
		glm::vec3 m_CameraDirection;
		glm::vec3 m_Up; 
		glm::vec3 m_CameraRight;
		glm::vec3 m_CameraUp;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_VP;



	public:
		static Camera* getCurrentCamera();
		static void setCurrentCamera(Camera* cam);

		Camera();
		~Camera();

		void OnUpdatePos(glm::vec3 pos_speeds);
		void OnUpdateTarget(glm::vec3 target_speeds);
		void OnUpdateFOV(float fov);
		void OnUpdate();
		void OnRender(std::vector<Shader*>& shaders);
		void OnImGuiRender();

		glm::mat4 getVP() const {return m_VP;}
		glm::vec3 getPosition() const {return m_CameraPos;}


};