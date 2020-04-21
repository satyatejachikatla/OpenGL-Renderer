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

#include <TestSphere.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestSphere::TestSphere() 
	: m_Sphere("./res/textures/Box.png")
	{

		shader_list.push_back(m_Sphere.m_Shader.get());

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestSphere::~TestSphere() {

	}

	void TestSphere::OnUpdate(float deltaTime) {
		m_Sphere.OnUpdate();
	}
	void TestSphere::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		//glCall(glEnable(GL_CULL_FACE));

		m_Sphere.OnRender();
	}
	void TestSphere::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Sphere.OnImGuiRender();
	}

}