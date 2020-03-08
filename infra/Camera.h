#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
	private:
		static Camera* m_CurrentCam;

		glm::mat4 m_Proj;
		glm::mat4 m_View;

		glm::mat4 m_VP;

		glm::vec3 m_Translation;

	public:
		static Camera* getCurrentCamera();
		static void setCurrentCamera(Camera* cam);

		Camera(glm::vec2 grid_x,glm::vec2 grid_y,glm::vec2 grid_z,bool perspective);
		Camera(float fov,float aspect,float near,float far);
		~Camera();

		void OnUpdate(glm::vec3 update_Translation);
		void OnUpdate(glm::mat4 update_Mat);
		void OnImGuiRender();

		glm::mat4 getVP() const {return m_VP;}


};