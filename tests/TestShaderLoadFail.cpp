#include <glErrors.h>

#include <TestShaderLoadFail.h>


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

#include <InputSystem.h>

namespace test {

	TestShaderLoadFail::TestShaderLoadFail() 
		: shader_name("./objects/shaders/My.shader"),
		  texture_name("res/textures/tile.jpg"){

		glCall(window = glfwGetCurrentContext());
		glCall(glfwGetWindowSize(window, &width, &height));
		m_Proj = glm::ortho(0.0f,float(width),0.0f,float(height),-1.0f,1.0f);

		std::cout << width << " " << height << std::endl;

		float positions[] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//0
			0.0f, height, 0.0f, 0.0f, 1.0f, 0.0f,//1
			width, height, 0.0f, 1.0f, 1.0f, 1.0f,//2
			width, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//3
		};

		unsigned int indices[] = {
			0,1,2,
			0,2,3
		};

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(positions,4*6*sizeof(*positions));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VBO,layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,6);

		m_Texture = std::make_unique<Texture>(texture_name.c_str());
		m_Texture->Bind(0);

		m_Shader = std::make_unique<Shader>(shader_name.c_str());

	}
	TestShaderLoadFail::~TestShaderLoadFail() {

	}

	void TestShaderLoadFail::OnUpdate(float deltaTime) {

	}
	void TestShaderLoadFail::OnRender() {
		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT));

		double xpos, ypos;
		glCall(glfwGetCursorPos(window, &xpos, &ypos));

		if(m_Shader->isLoadFailed()|| glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS){
			m_Shader.reset();
			m_Shader = std::make_unique<Shader>(shader_name.c_str());
		} else {
			m_Texture->Bind(0);
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_P",m_Proj);
			m_Shader->SetUniform1f("u_Time",glfwGetTime());
			m_Shader->SetUniformVec2f("u_Resolution",glm::vec2(width,height));
			m_Shader->SetUniformVec2f("u_Mouse",glm::vec2(xpos,ypos));
			m_Shader->SetUniform1i("u_TextureChannel",0);
			m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);
		}

	}
	void TestShaderLoadFail::OnImGuiRender() {
	}

}