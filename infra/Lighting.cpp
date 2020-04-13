#include <Lighting.h>


Lighting::Lighting(glm::vec3 Position,glm::vec3 Color) 
	: m_Position(Position) , 
	  m_Color(Color) ,
	  m_Ambient(glm::vec3(1.0f,1.0f,1.0f)) ,
	  m_Diffuse(glm::vec3(1.0f,1.0f,1.0f)) ,
	  m_Specular(glm::vec3(1.0f,1.0f,1.0f))  {
}
Lighting::~Lighting(){

}

void Lighting::OnUpdatePos(glm::vec3 pos_or_speed,bool is_pos){
	if(is_pos) {
		m_Position = pos_or_speed; 
	} else {
		m_Position += pos_or_speed;
	}
}
void Lighting::OnUpdateColor(glm::vec3 Color){
	m_Color = Color;
}

void Lighting::OnUpdateAmbient(glm::vec3 ambient){
	m_Ambient  = ambient;
}
void Lighting::OnUpdateDiffuse(glm::vec3 diffuse){
	m_Diffuse  = diffuse;
}
void Lighting::OnUpdateSpecular(glm::vec3 specular){
	m_Specular = specular;
}

void Lighting::OnUpdateShader(std::vector<Shader*>& shaders){
	for(auto shader : shaders) {

		//shader->SetUniformVec3f("light.position",m_Position);
		//shader->SetUniformVec3f("light.color",m_Color);

		//shader->SetUniformVec3f("light.ambient",m_Ambient);
		//shader->SetUniformVec3f("light.diffuse",m_Diffuse);
		//shader->SetUniformVec3f("light.specular",m_Specular);
	}
}
void Lighting::OnImGuiRender(){

}
