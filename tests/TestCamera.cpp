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

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestCamera::TestCamera() {


		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(nullptr,5*sizeof(Vertex));
		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();
		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./res/shaders/Basic.shader");
		m_Texture = std::make_unique<Texture>("./res/textures/Night_Dance.jpg");
		
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture",0);

		Camera::setCurrentCamera(&m_Camera);
	}
	TestCamera::~TestCamera() {
		glCall(glDisable(GL_CULL_FACE));
	}

	void TestCamera::OnUpdate(float deltaTime) {
	}
	void TestCamera::OnRender() {

		Vertex vertices[] = {
			{ {-1.0f,  0.0f, 0.0f} ,  {0.0f, 0.0f, 0.0f} ,  {0.0f, 0.0f} ,  0 } , //0
			{ { 1.0f,  0.0f, 0.0f} ,  {0.0f, 0.0f, 0.0f} ,  {1.0f, 1.0f} ,  0 } , //1
			{ { 0.0f,  1.0f, 0.0f} ,  {0.0f, 0.0f, 0.0f} ,  {0.5f, 0.5f} ,  0 } , //2
			{ { 0.0f,  0.0f,-1.0f} ,  {0.0f, 0.0f, 0.0f} ,  {0.0f, 1.0f} ,  0 } , //3
			{ { 0.0f,  0.0f, 1.0f}  , {0.0f, 0.0f, 0.0f} ,  {1.0f, 0.0f} ,  0 } , //4
		};

		unsigned int indices1[] = {
			4,1,2,
			0,4,2,
			1,3,2,
			3,0,2,
			0,1,4,
			0,3,1
		};

		unsigned int indices2[] = {
			2,1,4,
			2,4,0,
			2,3,1,
			2,0,3,
			4,1,0,
			1,3,0
		};

		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
		glCall(glEnable(GL_CULL_FACE));

		Renderer renderer;

		glm::mat4 mvp = m_Camera.getVP();

		m_VBO->Bind(vertices);
		m_Texture->Bind(0);
		m_Shader->Bind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices1,18);
		m_Shader->SetUniformMat4f("u_MVP",mvp);
		renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices2,18);
		glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(2.0f,0.0f,0.0f));
		m_Shader->SetUniformMat4f("u_MVP",mvp * model);
		renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

		//std::cout<<glm::to_string(mvp)<<std::endl;

	}
	void TestCamera::OnImGuiRender() {
		m_Camera.OnImGuiRender();
	}

}