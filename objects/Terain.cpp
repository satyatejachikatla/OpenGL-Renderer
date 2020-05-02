#include <Terain.h>

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Camera.h>
#include <Lighting.h>

#include <glErrors.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <cmath>

namespace objects {

	Terain::Terain(const char* img) : Object(){


		unsigned int  sectorCount = 100;
		unsigned int  stackCount  = 100;


		std::vector<unsigned int> indices;

		for(int stackStep = 0; stackStep <= stackCount; ++stackStep)
		{

			for(int sectorStep = 0; sectorStep <= sectorCount; ++sectorStep)
			{

				Vertex v[4];

				v[0].vertexCoords = glm::vec3(sectorStep,0.0f,stackStep);
				v[1].vertexCoords = glm::vec3(sectorStep+1.0f,0.0f,stackStep);
				v[2].vertexCoords = glm::vec3(sectorStep+1.0f,0.0f,stackStep+1.0f);
				v[3].vertexCoords = glm::vec3(sectorStep,0.0f,stackStep+1.0f);

				// vertex tex coord (s, t) range between [0, 1]
				v[0].textureCoords = glm::vec2(0.0f,0.0f);
				v[1].textureCoords = glm::vec2(1.0f,0.0f);
				v[2].textureCoords = glm::vec2(1.0f,1.0f);
				v[3].textureCoords = glm::vec2(0.0f,1.0f);

				v[0].normal = v[1].normal = v[2].normal = v[3].normal = glm::vec3(1.0f,1.0f,1.0f);
				v[0].textureId = v[1].textureId = v[2].textureId = v[3].textureId = 0;
				v[0].color = v[1].color = v[2].color = v[3].color = glm::vec3(1.0f,1.0f,1.0f);

				int n_curr_vetices = m_Vertices.size();

				m_Vertices.push_back(v[0]);
				m_Vertices.push_back(v[1]);
				m_Vertices.push_back(v[2]);
				m_Vertices.push_back(v[3]);
				
				indices.push_back(n_curr_vetices+2);
				indices.push_back(n_curr_vetices+1);
				indices.push_back(n_curr_vetices+0);
				indices.push_back(n_curr_vetices+0);
				indices.push_back(n_curr_vetices+3);
				indices.push_back(n_curr_vetices+2);
			}
		}

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(m_Vertices.data(),m_Vertices.size()*sizeof(Vertex));

		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();

		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./objects/shaders/Dev.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>(img);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(),indices.size());

		/*
		for(int i =0 ;i < 24 ; i++) {
			std::cout << "Vertex " << i << std::endl;
			std::cout <<glm::to_string(m_Vertices[i].vertexCoords)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].color)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].textureCoords)<<std::endl;
			std::cout <<m_Vertices[i].textureId<<std::endl;
		}
		*/
	}

	Terain::~Terain(){
		
	}

	void Terain::OnUpdate(){
		Object::OnUpdate();
		m_Shader->Bind();
		glCall(m_Shader->SetUniform1f("up_down_theta",glfwGetTime()));
		glCall(m_Shader->SetUniform1f("height_limiter",0.1));
	}

	void Terain::OnRender(){

		glm::mat4 m = m_Model;

		std::vector<Shader*> shader_list;
		shader_list.push_back(m_Shader.get());

		Camera* camera = Camera::getCurrentCamera();
		if(camera)
			camera->OnRender(shader_list);

		m_Shader->Bind();

		/* Material Properties */
		m_Shader->SetUniform1f("u_Material.selectColor",0.0f);
		m_Shader->SetUniform1f("u_Material.shininess",32.0f);
		m_Shader->SetUniform1i("u_Material.texture",0);

		m_Shader->SetUniform1i("u_Material.isSpecularMap",0);
		m_Shader->SetUniform1i("u_Material.specularMap",0);

		m_Shader->SetUniformMat4f("u_M",m);

		m_Texture->Bind(0);

		/* Draw Call */
		m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

	}
	void Terain::OnImGuiRender(){
		Object::OnImGuiRender();
	}

}