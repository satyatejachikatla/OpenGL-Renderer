#include <glErrors.h>
#include <Camera.h>
#include <imgui/imgui.h>
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


Camera::Camera(glm::vec2 a,glm::vec2 b,glm::vec2 c,bool perspective) {

	m_Translation = glm::vec3(0,0,-1);
	if(perspective){
		m_Proj=glm::frustum(a[0],a[1],b[0],b[1],c[0],c[1]);
	} else {
		m_Proj=glm::ortho(a[0],a[1],b[0],b[1],c[0],c[1]);
	}
	m_View=glm::translate(glm::mat4(1.0f),m_Translation);

	m_VP = m_Proj * m_View;

	//std::cout<<glm::to_string(m_VP)<<std::endl;
}

Camera::Camera(float fov,float aspect,float near,float far) {

	m_Translation = glm::vec3(0,0,0);

	m_Proj=glm::perspective(fov,aspect,near,far);
	m_View=glm::translate(glm::mat4(1.0f),m_Translation);

	m_VP = m_Proj * m_View;

	//std::cout<<glm::to_string(m_VP)<<std::endl;
}

Camera::~Camera() {

}

void Camera::OnUpdate(glm::vec3 update_Translation) {

	m_Translation += update_Translation;
	m_View = glm::translate(glm::mat4(1.0f),m_Translation);
	m_VP = m_Proj * m_View;

	//std::cout<<glm::to_string(m_VP)<<std::endl;
}
void Camera::OnUpdate(glm::mat4 update_Mat) {

	m_View = update_Mat;
	m_VP = m_Proj * m_View;

	//std::cout<<glm::to_string(m_VP)<<std::endl;
}

void Camera::OnImGuiRender() {
	ImGui::SliderFloat3("Translation", &m_Translation.x, -5.0f, 5.0f);
	m_View = glm::translate(glm::mat4(1.0f),m_Translation);
	m_VP = m_Proj * m_View;
}
