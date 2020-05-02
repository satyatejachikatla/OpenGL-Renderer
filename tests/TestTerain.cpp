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

#include <TestTerain.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestTerain::TestTerain() 
	: m_Terain("./res/textures/ocean.png")
	{

		m_LightList.m_Lights.push_back(std::make_shared<light::DirectionLight>(glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f)));

		shader_list.push_back(m_Terain.m_Shader.get());

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestTerain::~TestTerain() {

	}

	void TestTerain::OnUpdate(float deltaTime) {
		m_Terain.OnUpdate();
	}
	void TestTerain::OnRender() {
		glCall(glClearColor(0xff/256.0f,0xe6/256.0f,0x7e/256.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));
		m_LightList.OnRender(shader_list);

		m_Terain.OnRender();

	}
	void TestTerain::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Terain.OnImGuiRender();
		m_LightList.OnImGuiRender();
	}

}