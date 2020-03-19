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

	m_CameraPos = glm::vec3(0.0f, 3.0f, 3.0f);

	m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_CameraDirection = glm::normalize(m_CameraPos - m_CameraTarget);

	m_Up = glm::vec3(0.0f, 1.0f, 0.0f); 
	m_CameraRight = glm::normalize(glm::cross(m_Up, m_CameraDirection));

	m_CameraUp = glm::cross(m_CameraDirection, m_CameraRight);

	m_View = glm::lookAt(m_CameraPos, 
						 m_CameraTarget, 
						 m_CameraUp);

	const float fov = 45;
	m_Projection = glm::perspective(glm::radians(fov), 1.0f , 0.1f, 100.0f);  
}

Camera::~Camera() {

}

void Camera::OnUpdate(float r_speed,float i_speed,float camY) {
	
	static float angle = 0;
	static float radius = 5.0f;
	static float camY_t = 3.0f;

	angle += r_speed;	
	radius += i_speed;
	camY_t += camY;
	
	float camX = sin(angle) * radius;
	float camZ = cos(angle) * radius;

	m_View = glm::lookAt(glm::vec3(camX, camY_t ,camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0 ,0.0));

	m_VP = m_Projection * m_View;
}

void Camera::OnImGuiRender() {
/*	
	ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
	m_View = glm::translate(glm::mat4(1.0f),m_Translation);
	m_VP = m_Proj * m_View;
*/
}

/* Debug examples	
	//std::cout<<glm::to_string(m_VP)<<std::endl; 
*/