#include "LoadedObject.h"

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Camera.h>
#include <Lighting.h>
#include <sstream>

namespace objects {

	LoadedObject::LoadedObject(const char* objfile,const char* texfile) : Object(){

		m_Data = LoadObject(objfile);
		ASSERT(m_Data);


		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(m_Data->vertices.data(),m_Data->vertices.size()*sizeof(Vertex));

		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();

		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./objects/shaders/GenericObject.shader");
		m_Texture = std::make_unique<Texture>(texfile);
		
		m_Shader->Bind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Data->indices.data(),m_Data->indices.size());

	}

	LoadedObject::~LoadedObject(){
		
	}

	void LoadedObject::OnUpdate(){
		Object::OnUpdate();
	}

	void LoadedObject::OnRender(){

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
	void LoadedObject::OnImGuiRender(){
		Object::OnImGuiRender();
	}

}