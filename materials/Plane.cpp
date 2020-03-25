#include "Plane.h"

#include <GL/glew.h>
#include <imgui/imgui.h>
namespace material {

	Plane::Plane(char* img) : Material(){

		/* Face */
		m_Vertices[0].vertexCoords = {-1.0f, -1.0f, 0.0f};
		m_Vertices[1].vertexCoords = { 1.0f, -1.0f, 0.0f};
		m_Vertices[2].vertexCoords = { 1.0f,  1.0f, 0.0f};
		m_Vertices[3].vertexCoords = {-1.0f,  1.0f, 0.0f};

		/* Default Vertex Properties */
		for(int i =0 ; i < 4 ; i++) {
			m_Vertices[i].color = {1.0f, 1.0f, 1.0f};
			switch(i%4) {
			case 0:
				m_Vertices[i].textureCoords = {0.0f, 0.0f};
				break;
			case 1:
				m_Vertices[i].textureCoords = {0.0f, 1.0f};
				break;
			case 2:
				m_Vertices[i].textureCoords = {1.0f, 1.0f};
				break;
			case 3:
				m_Vertices[i].textureCoords = {1.0f, 0.0f};
				break;
			default:
				ASSERT(false);
			}
			m_Vertices[i].textureId = 0;
		}


		/* Default Index Ordering */
		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(m_Vertices,4*sizeof(Vertex));

		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();

		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./res/shaders/Box.shader");
		m_Texture = std::make_unique<Texture>(img);
		
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture",0);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,6);

		m_Model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));

		/*
		for(int i =0 ;i < 4 ; i++) {
			std::cout << "Vertex " << i << std::endl;
			std::cout <<glm::to_string(m_Vertices[i].vertexCoords)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].color)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].textureCoords)<<std::endl;
			std::cout <<m_Vertices[i].textureId<<std::endl;
		}
		*/
	}

	Plane::~Plane(){
		
	}

	void Plane::OnUpdate(){
		Material::OnUpdate();
	}

	glm::mat4 Plane::OnRender(){

		glm::mat4 mvp = Material::OnRender();

		if (mvp == glm::mat4(0.0f))
			return mvp;	

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP",mvp);
		m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

	}
	void Plane::OnImGuiRender(){
		Material::OnImGuiRender();
	}

}