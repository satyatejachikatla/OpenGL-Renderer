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

	glCall(GLFWwindow* window = glfwGetCurrentContext());
	glCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));

	m_CameraPos    = glm::vec3(0.0f, 3.0f, 3.0f);
	m_CameraFront  = glm::vec3(0.0f, -3.0f, -3.0f);

	m_Up           = glm::vec3(0.0f, 1.0f, 0.0f);

	const float fov = 45;

	m_Projection = glm::perspective(glm::radians(fov), 1.0f , 0.1f, 100.0f);

	OnUpdate();
}

Camera::~Camera() {
	if (getCurrentCamera() == this)
		setCurrentCamera(nullptr);
}

void Camera::OnUpdatePos(glm::vec3 pos_speeds) {

	glm::vec3 x_update = glm::normalize(m_CameraRight) * pos_speeds.x;
	glm::vec3 y_update = glm::normalize(m_CameraUp) * pos_speeds.y;
	glm::vec3 z_update = glm::normalize(m_CameraDirection) * pos_speeds.z;

	m_CameraPos += x_update + y_update + z_update;

	OnUpdate();
}

void Camera::OnUpdateTarget(glm::vec3 direction) {

	if(direction == glm::vec3(0.0f,0.0f,0.0f))
		return;

	m_CameraFront = direction;

	OnUpdate();
}

void Camera::OnUpdateFOV(float fov) {

	m_Projection = glm::perspective(glm::radians(fov), 1.0f , 0.1f, 100.0f);

	OnUpdate();
}

void Camera::OnUpdate() {

	m_CameraTarget = m_CameraPos + m_CameraFront;
	m_CameraDirection = glm::normalize(m_CameraPos - m_CameraTarget);
	m_CameraRight = glm::normalize(glm::cross(m_Up, m_CameraDirection));
	m_CameraUp = glm::cross(m_CameraDirection, m_CameraRight);

	m_View = glm::lookAt(m_CameraPos, m_CameraTarget, m_CameraUp);
	m_VP = m_Projection * m_View;

/*
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Pos " <<glm::to_string(m_CameraPos)<<std::endl;
	std::cout << "Front " <<glm::to_string(m_CameraFront)<<std::endl;
	std::cout << "Target " <<glm::to_string(m_CameraTarget)<<std::endl;
	std::cout << "Direction "<<glm::to_string(m_CameraDirection)<<std::endl;
	std::cout << "Right " << glm::to_string(m_CameraRight)<<std::endl;
	std::cout << "Up " << glm::to_string(m_CameraUp)<<std::endl; 
*/
}

void Camera::OnImGuiRender() {
	
	ImGui::SliderFloat3("Camera Target", &m_CameraTarget.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("Camera Position", &m_CameraPos.x, -10.0f, 10.0f);
	OnUpdate();
}
