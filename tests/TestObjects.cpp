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
#include <Lighting.h>

#include <TestObjects.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestObjects::TestObjects() 
	: m_Box("./res/textures/Box.png"),
	  m_Box_refrence("./res/textures/Night_Dance.jpg"),
	  m_Plane("./res/textures/Night_Dance.jpg") 
	{

		m_LightList.m_Lights.push_back(std::make_shared<light::PointLight>(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f)));
		m_LightList.m_Lights.push_back(std::make_shared<light::DirectionLight>(glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f)));

		shader_list.push_back(m_Box.m_Shader.get());
		shader_list.push_back(m_Box_refrence.m_Shader.get());
		shader_list.push_back(m_Plane.m_Shader.get());

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestObjects::~TestObjects() {

	}

	void TestObjects::OnUpdate(float deltaTime) {
		m_Box.OnUpdate();
		m_Box_refrence.OnRender();
		m_Plane.OnUpdate();
	}
	void TestObjects::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		m_LightList.OnRender(shader_list);

		m_Box.OnRender();
		m_Box_refrence.OnRender();
		m_Plane.OnRender();

	}
	void TestObjects::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Box.OnImGuiRender();
		m_Box_refrence.OnImGuiRender();
		m_Plane.OnImGuiRender();
		m_LightList.OnImGuiRender();
	}

}