#include "Plane.h"

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Camera.h>
#include <Lighting.h>
#include <sstream>

namespace objects {

	Plane::Plane(const char* img) : Object(){

		/* Face */
		m_Vertices[0].vertexCoords = {-1.0f, -1.0f, 0.0f};
		m_Vertices[1].vertexCoords = { 1.0f, -1.0f, 0.0f};
		m_Vertices[2].vertexCoords = { 1.0f,  1.0f, 0.0f};
		m_Vertices[3].vertexCoords = {-1.0f,  1.0f, 0.0f};

		m_Vertices[0].normal = m_Vertices[1].normal = m_Vertices[2].normal= m_Vertices[3].normal = { 0.0f, 0.0f, 1.0f};

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
			m_Vertices[i].textureId = 0.0f;
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

		m_Shader = std::make_unique<Shader>("./objects/shaders/GenericObject.shader");
		m_Texture = std::make_unique<Texture>(img);
		
		m_Shader->Bind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,6);

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
		Object::OnUpdate();
	}

	void Plane::OnRender(){

		glm::mat4 m = m_Model;

		std::vector<Shader*> shader_list;
		shader_list.push_back(m_Shader.get());

		Camera* camera = Camera::getCurrentCamera();
		if(camera)
			camera->OnRender(shader_list);

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_M",m);

		/* Material Properties */
		m_Shader->SetUniform1f("u_Material.selectColor",0.0f);
		m_Shader->SetUniform1f("u_Material.shininess",32.0f);
		m_Shader->SetUniform1i("u_Material.texture",0);

		m_Shader->SetUniform1i("u_Material.isSpecularMap",0);
		m_Shader->SetUniform1i("u_Material.specularMap",0);

		m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

	}
	void Plane::OnImGuiRender(){
		std::stringstream ss[3];

		ss[0] << m_ObjectId << " Translation";
		ss[1] << m_ObjectId << " Rotation";
		ss[2] << m_ObjectId << " Scale";

		ImGui::SliderFloat3(ss[0].str().c_str(), &m_Translate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3(ss[1].str().c_str(), &m_Rotate.x, -180.0f, 180.0f);
		ImGui::SliderFloat2(ss[2].str().c_str(), &m_Scale.x, 0.0f, 5.0f);
		OnUpdate();
	}

}