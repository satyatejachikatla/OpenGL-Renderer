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
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestTerain::TestTerain() 
	: m_Terain("./res/textures/ocean.png"),
	  m_Boat("objects/objs/boat.obj","./res/textures/boat.jpg")
	{

		m_LightList.m_Lights.push_back(std::make_shared<light::DirectionLight>(glm::vec3(0.0f,-1.0f,-1.0f),glm::vec3(1.0f,1.0f,1.0f)));

		shader_list.push_back(m_Terain.m_Shader.get());
		shader_list.push_back(m_Boat.m_Shader.get());


		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		Camera::setCurrentCamera(&m_Camera);

	}
	TestTerain::~TestTerain() {

	}

	void TestTerain::OnUpdate(float deltaTime) {
		static glm::vec3 bob = glm::vec3(0.0f,0.0f,0.0f);
		
		bob.x = sin(glfwGetTime())*1.5;
		bob.z = cos(glfwGetTime())*1.5;

		m_Terain.OnUpdate();
		m_Boat.OnUpdateRotate(bob);
	}
	void TestTerain::OnRender() {
		glCall(glClearColor(0xff/256.0f,0xe6/256.0f,0x7e/256.0f,0.0f));
		//glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));
		m_LightList.OnRender(shader_list);

		m_Terain.OnRender();
		m_Boat.OnRender();

	}
	void TestTerain::OnImGuiRender() {
		m_Camera.OnImGuiRender();
		m_Terain.OnImGuiRender();
		m_Boat.OnImGuiRender();
		m_LightList.OnImGuiRender();
	}

}