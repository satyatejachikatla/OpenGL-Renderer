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

#include <TestLoadingObj.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestLoadingObj::TestLoadingObj() 
	: m_Obj("./objects/objs/stall.obj","./res/textures/stallTexture.png")
	{

		m_LightList.m_Lights.push_back(std::make_shared<light::PointLight>(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f)));

		shader_list.push_back(m_Obj.m_Shader.get());

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestLoadingObj::~TestLoadingObj() {

	}

	void TestLoadingObj::OnUpdate(float deltaTime) {
		m_Obj.OnUpdate();
	}
	void TestLoadingObj::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		//glCall(glEnable(GL_CULL_FACE));

		m_LightList.OnRender(shader_list);

		m_Obj.OnRender();

	}
	void TestLoadingObj::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Obj.OnImGuiRender();
		m_LightList.OnImGuiRender();
	}

}