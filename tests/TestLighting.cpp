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

	TestLighting::TestLighting() {
		
		m_Boxs.m_Objects.push_back(std::make_shared<objects::Box>("./res/textures/box_with_metal.png"));

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));


		Camera::setCurrentCamera(&m_Camera);

	}
	TestLighting::~TestLighting() {

	}

	void TestLighting::OnUpdate(float deltaTime) {
		m_Boxs.OnUpdate();
	}
	void TestLighting::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		m_Boxs.OnRender();

	}
	void TestLighting::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Boxs.OnImGuiRender();
	}

}