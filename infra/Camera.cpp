#include <glErrors.h>
#include <Camera.h>
#include <imgui/imgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

Camera* Camera::m_CurrentCam=nullptr;
Camera* Camera::getCurrentCamera() {
	return m_CurrentCam;
}
void Camera::setCurrentCamera(Camera* cam) {
	m_CurrentCam=cam;
}


Camera::Camera() {

	m_CameraPos    = glm::vec3(0.0f, 3.0f, 3.0f);

	m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Straf        = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Up           = glm::vec3(0.0f, 1.0f, 0.0f);

	const float fov = 45;

	OnUpdate();
	
	m_Projection = glm::perspective(glm::radians(fov), 1.0f , 0.1f, 100.0f);
}

Camera::~Camera() {

}

void Camera::OnUpdatePos(glm::vec3 pos_speeds) {

	glm::vec3 x_update = glm::normalize(m_CameraRight) * pos_speeds.x;
	glm::vec3 y_update = glm::normalize(m_CameraUp) * pos_speeds.y;
	glm::vec3 z_update = glm::normalize(m_CameraDirection) * pos_speeds.z;

	m_CameraPos += x_update + y_update + z_update;
	m_CameraTarget += x_update + y_update + z_update;

	OnUpdate();
}

void Camera::OnUpdateTarget(glm::vec3 target_speeds) {

	glm::vec3 x_update = glm::normalize(m_CameraRight) * target_speeds.x;
	glm::vec3 y_update = glm::normalize(m_CameraUp) * target_speeds.y;
	glm::vec3 z_update = glm::normalize(m_CameraDirection) * target_speeds.z;

	m_CameraTarget += x_update + y_update + z_update;

	OnUpdate();
}

void Camera::OnUpdateStraf(glm::vec3 Straf) {

	m_Straf = Straf;
	OnUpdate();
}

void Camera::OnUpdate() {

	m_CameraTarget_with_straf = m_CameraTarget - m_Straf;
	m_CameraDirection = glm::normalize(m_CameraPos - m_CameraTarget_with_straf);
	m_CameraRight = glm::normalize(glm::cross(m_Up, m_CameraDirection));
	m_CameraUp = glm::cross(m_CameraDirection, m_CameraRight);
	m_View = glm::lookAt(m_CameraPos, 
						 m_CameraTarget_with_straf, 
						 m_CameraUp);

	m_VP = m_Projection * m_View;

	/*
	std::cout << "Actual Target " <<glm::to_string(m_CameraTarget)<<std::endl;
	std::cout << "Straf " <<glm::to_string(m_Straf)<<std::endl;
	std::cout << "Computed Target 	" <<glm::to_string(m_CameraTarget_with_straf)<<std::endl;
	*/

}

void Camera::OnImGuiRender() {
	
	ImGui::SliderFloat3("Camera Target", &m_CameraTarget.x, -1.0f, 1.0f);
	ImGui::SliderFloat3("Camera Position", &m_CameraPos.x, -1.0f, 1.0f);
	OnUpdate();
}
