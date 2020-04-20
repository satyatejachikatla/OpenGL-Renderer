#include <glErrors.h>
#include <TestCamera.h>

#include <GL/glew.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>

#include <memory>

#include <TestLighting.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestLighting::TestLighting() {

		std::shared_ptr<objects::Box> box = std::make_shared<objects::Box>("./res/textures/box_with_metal.png");

		m_Boxs.m_Objects.push_back(box);
		m_LightList.m_Lights.push_back(std::make_shared<light::PointLight>(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f)));
		m_LightList.m_Lights.push_back(std::make_shared<light::DirectionLight>(glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f)));
		splight = std::make_shared<light::SpotLight>(m_Camera.getPosition(),m_Camera.getCameraFront(),glm::vec3(1.0f,1.0f,1.0f));
		m_LightList.m_Lights.push_back(splight);

		shader_list.push_back(box->m_Shader.get());

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestLighting::~TestLighting() {

	}

	void TestLighting::OnUpdate(float deltaTime) {

		splight->OnUpdatePosition(m_Camera.getPosition(),true);
		splight->OnUpdateDirection(m_Camera.getCameraFront());

		m_Boxs.OnUpdate();
	}
	void TestLighting::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		m_LightList.OnRender(shader_list);
		m_Boxs.OnRender();

	}
	void TestLighting::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Boxs.OnImGuiRender();
		m_LightList.OnImGuiRender();
	}

}