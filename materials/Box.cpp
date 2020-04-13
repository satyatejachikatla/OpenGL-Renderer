#include "Box.h"

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Camera.h>
namespace material {

	Box::Box(char* img) : Material(){

		/* Face 0 */
		m_Vertices[0].vertexCoords = {-1.0f, -1.0f, -1.0f};
		m_Vertices[1].vertexCoords = {-1.0f,  1.0f, -1.0f};
		m_Vertices[2].vertexCoords = { 1.0f,  1.0f, -1.0f};
		m_Vertices[3].vertexCoords = { 1.0f, -1.0f, -1.0f};

		m_Vertices[0].normal = m_Vertices[1].normal = m_Vertices[2].normal= m_Vertices[3].normal = { 0.0f, 0.0f,-1.0f};

		/* Face 1 */
		m_Vertices[4].vertexCoords = {-1.0f, -1.0f, 1.0f};
		m_Vertices[5].vertexCoords = { 1.0f, -1.0f, 1.0f};
		m_Vertices[6].vertexCoords = { 1.0f,  1.0f, 1.0f};
		m_Vertices[7].vertexCoords = {-1.0f,  1.0f, 1.0f};

		m_Vertices[4].normal = m_Vertices[5].normal = m_Vertices[6].normal= m_Vertices[7].normal = { 0.0f, 0.0f, 1.0f};

		/* Face 2 */
		m_Vertices[8].vertexCoords  = m_Vertices[5].vertexCoords;
		m_Vertices[9].vertexCoords  = m_Vertices[3].vertexCoords;
		m_Vertices[10].vertexCoords = m_Vertices[2].vertexCoords;
		m_Vertices[11].vertexCoords = m_Vertices[6].vertexCoords;

		m_Vertices[8].normal = m_Vertices[9].normal = m_Vertices[10].normal= m_Vertices[11].normal = { 1.0f, 0.0f, 0.0f};

		/* Face 3 */
		m_Vertices[12].vertexCoords = m_Vertices[0].vertexCoords;
		m_Vertices[13].vertexCoords = m_Vertices[4].vertexCoords;
		m_Vertices[14].vertexCoords = m_Vertices[7].vertexCoords;
		m_Vertices[15].vertexCoords = m_Vertices[1].vertexCoords;

		m_Vertices[12].normal = m_Vertices[13].normal = m_Vertices[14].normal= m_Vertices[15].normal = {-1.0f, 0.0f, 0.0f};

		/* Face 4 */
		m_Vertices[16].vertexCoords = m_Vertices[0].vertexCoords;
		m_Vertices[17].vertexCoords = m_Vertices[3].vertexCoords;
		m_Vertices[18].vertexCoords = m_Vertices[5].vertexCoords;
		m_Vertices[19].vertexCoords = m_Vertices[4].vertexCoords;

		m_Vertices[16].normal = m_Vertices[17].normal = m_Vertices[18].normal= m_Vertices[19].normal = { 0.0f,-1.0f, 0.0f};

		/* Face 5 */
		m_Vertices[20].vertexCoords = m_Vertices[1].vertexCoords;
		m_Vertices[21].vertexCoords = m_Vertices[7].vertexCoords;
		m_Vertices[22].vertexCoords = m_Vertices[6].vertexCoords;
		m_Vertices[23].vertexCoords = m_Vertices[2].vertexCoords;

		m_Vertices[20].normal = m_Vertices[21].normal = m_Vertices[22].normal= m_Vertices[23].normal = { 0.0f, 1.0f, 0.0f};

		/* Default Vertex Properties */
		for(int i =0 ; i < 24 ; i++) {
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
			m_Vertices[i].textureId = 1.0f;
		}


		/* Default Index Ordering */
		unsigned int indices[36];
		for(int i=0,j=0;i<36 && j<24 ;i+=6,j+=4) {
			indices[i]   = j;
			indices[i+1] = j+1;
			indices[i+2] = j+2;
			indices[i+3] = j+2;
			indices[i+4] = j+3;
			indices[i+5] = j;
		}

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(m_Vertices,24*sizeof(Vertex));

		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();

		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./res/shaders/Material.shader");
		m_Texture = std::make_unique<Texture>(img);
		m_Texture_2 = std::make_unique<Texture>("./res/textures/box_with_metal_specular.png");
		

		m_Shader->Bind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,36);

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

	Box::~Box(){
		
	}

	void Box::OnUpdate(){
		Material::OnUpdate();
	}

	glm::mat4 Box::OnRender(){

		glm::mat4 m = Material::OnRender();
		Camera* camera = Camera::getCurrentCamera();

		if (m == glm::mat4(0.0f))
			return glm::mat4(0.0f);
		if (!camera)
			return glm::mat4(m);

		m_Texture->Bind(1);
		m_Texture_2->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_M",m);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_VP",camera->getVP());

		m_Shader->Bind();
		m_Shader->SetUniformVec3f("u_ViewPos",camera->getPosition());

		/* Properties */
		m_Shader->SetUniform1f("u_Material.selectColor",0.0f);
		m_Shader->SetUniform1f("u_Material.shininess",32.0f);
		m_Shader->SetUniform1i("u_Material.texture",1);

		m_Shader->SetUniform1i("u_Material.isSpecularMap",1);
		m_Shader->SetUniform1i("u_Material.specularMap",0);

		m_Shader->SetUniformVec3f("u_Light.position",glm::vec3(0.0f,0.f,0.0f));

		glm::vec3 lightColor;
		lightColor.r = 1.0f;
		lightColor.g = 1.0f;
		lightColor.b = 1.0f;

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
		glm::vec3 ambientColor = lightColor * glm::vec3(0.1f);

		m_Shader->SetUniformVec3f("u_Light.ambient",ambientColor);
		m_Shader->SetUniformVec3f("u_Light.diffuse",diffuseColor);
		m_Shader->SetUniformVec3f("u_Light.specular",glm::vec3(1.0f,1.0f,1.0f)*1.0f);

		/* Draw Call */
		m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

		return glm::mat4(m);

	}
	void Box::OnImGuiRender(){
		//ImGui::SliderFloat2("Specular ".c_str(), &m_Scale.x, 0.0f, 5.0f);
		Material::OnImGuiRender();
	}

}