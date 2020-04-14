#include <Lighting.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

PointLight::PointLight(glm::vec3 Position,glm::vec3 Color) 
	: m_Position(Position) , 
	  m_Color(Color) ,
	  m_Ambient(glm::vec3(1.0f,1.0f,1.0f)*0.1f) ,
	  m_Diffuse(glm::vec3(1.0f,1.0f,1.0f)*0.8f) ,
	  m_Specular(glm::vec3(1.0f,1.0f,1.0f))  {
}
PointLight::~PointLight(){

}

void PointLight::OnUpdatePos(glm::vec3 pos_or_speed,bool is_pos){
	if(is_pos) {
		m_Position = pos_or_speed; 
	} else {
		m_Position += pos_or_speed;
	}
}
void PointLight::OnUpdateColor(glm::vec3 Color){
	m_Color = Color;
}

void PointLight::OnUpdateAmbient(glm::vec3 ambient){
	m_Ambient  = ambient;
}
void PointLight::OnUpdateDiffuse(glm::vec3 diffuse){
	m_Diffuse  = diffuse;
}
void PointLight::OnUpdateSpecular(glm::vec3 specular){
	m_Specular = specular;
}

void PointLight::OnRender(std::vector<Shader*>& shaders){
	for(auto shader : shaders) {
		shader->Bind();
		shader->SetUniformVec3f("u_Light.position",m_Position);
		shader->SetUniformVec3f("u_Light.ambient",m_Color*m_Ambient);
		shader->SetUniformVec3f("u_Light.diffuse",m_Color*m_Diffuse);
		shader->SetUniformVec3f("u_Light.specular",m_Color*m_Specular);
	}
}
void PointLight::OnImGuiRender(){
	ImGui::SliderFloat3("Position ", &m_Position.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Ambient ", &m_Position.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Diffuse ", &m_Position.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Specular ", &m_Position.x, 0.0f, 1.0f);
}



LightList::LightList(){}
LightList::~LightList(){}

void LightList::OnRender(std::vector<Shader*>& shaders){
	for(int i=0;i<m_Lights.size();i++){
		m_Lights[i]->OnRender(shaders);
	}
}
void LightList::OnImGuiRender(){
	for(int i=0;i<m_Lights.size();i++){
		m_Lights[i]->OnImGuiRender();
	}
}