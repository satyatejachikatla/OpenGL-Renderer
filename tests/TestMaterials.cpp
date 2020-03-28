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

#include <TestMaterials.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestMaterials::TestMaterials() 
	: m_Box("./res/textures/Box.png"),
	  m_Box_refrence("./res/textures/Night_Dance.jpg"),
	  m_Plane("./res/textures/Night_Dance.jpg") 
	{


		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);
	}
	TestMaterials::~TestMaterials() {

	}

	void TestMaterials::OnUpdate(float deltaTime) {
		m_Box.OnUpdate();
		m_Box_refrence.OnRender();
		m_Plane.OnUpdate();
	}
	void TestMaterials::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		m_Box.OnRender();
		m_Box_refrence.OnRender();
		m_Plane.OnRender();

	}
	void TestMaterials::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Box.OnImGuiRender();
		m_Box_refrence.OnImGuiRender();
		m_Plane.OnImGuiRender();
	}

}