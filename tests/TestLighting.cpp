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

#include <TestLighting.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestLighting::TestLighting() 
	: m_Box("./res/textures/box_with_metal.png")
	  //m_Box_center("./res/textures/Box.png")
	{
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		//m_Box_center.m_Shader->SetUniform1f("u_SelectColorf",1.0f);

		Camera::setCurrentCamera(&m_Camera);

		//for (auto id : Shader::TotalRendererIDList()) std::cout << id << " ";
		//std::cout << std::endl;

	}
	TestLighting::~TestLighting() {

	}

	void TestLighting::OnUpdate(float deltaTime) {
		m_Box.OnUpdate();
	}
	void TestLighting::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		m_Box.OnRender();
		//m_Box_center.OnRender();

	}
	void TestLighting::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Box.OnImGuiRender();
	}

}