#include <Lighting.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


Light::Light()
	:	m_Color(glm::vec3(1.0f,1.0f,1.0f)) ,
		m_Ambient(glm::vec3(1.0f,1.0f,1.0f)*0.1f) ,
		m_Diffuse(glm::vec3(1.0f,1.0f,1.0f)*0.8f) ,
		m_Specular(glm::vec3(1.0f,1.0f,1.0f)) {
}
Light::Light(glm::vec3 Color)
	:	m_Color(Color) ,
		m_Ambient(Color*0.1f) ,
		m_Diffuse(Color*0.8f) ,
		m_Specular(Color*glm::vec3(1.0f,1.0f,1.0f)) {
}
void Light::OnUpdateColor(glm::vec3 Color){
	m_Color = Color;
}
void Light::OnUpdateAmbient(glm::vec3 ambient){
	m_Ambient  = ambient;
}
void Light::OnUpdateDiffuse(glm::vec3 diffuse){
	m_Diffuse  = diffuse;
}
void Light::OnUpdateSpecular(glm::vec3 specular){
	m_Specular = specular;
}
void Light::OnRender(std::vector<Shader*>& shaders){
	for(auto shader : shaders) {
		shader->Bind();
		shader->SetUniformVec3f("u_Light.ambient",m_Color*m_Ambient);
		shader->SetUniformVec3f("u_Light.diffuse",m_Color*m_Diffuse);
		shader->SetUniformVec3f("u_Light.specular",m_Color*m_Specular);
	}
}
void Light::OnImGuiRender(){
	ImGui::SliderFloat3("Ambient ", &m_Ambient.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Diffuse ", &m_Diffuse.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("Specular ", &m_Specular.x, 0.0f, 1.0f);
}



PointLight::PointLight(glm::vec3 Position,glm::vec3 Color) 
	: m_Position(Position) , 
	  Light(Color) {
}
PointLight::~PointLight(){

}
void PointLight::OnUpdatePosition(glm::vec3 pos_or_speed,bool is_pos){
	if(is_pos) {
		m_Position = pos_or_speed; 
	} else {
		m_Position += pos_or_speed;
	}
}
void PointLight::OnRender(std::vector<Shader*>& shaders){
	for(auto shader : shaders) {
		shader->Bind();
		shader->SetUniformVec3f("u_Light.position",m_Position);
	}
	Light::OnRender(shaders);
}
void PointLight::OnImGuiRender(){
	ImGui::SliderFloat3("Position ", &m_Position.x, 0.0f, 1.0f);
	Light::OnImGuiRender();
}


DirectionLight::DirectionLight(glm::vec3 Direction,glm::vec3 Color) 
	:	m_Direction(Direction),
		Light(Color) {
}
DirectionLight::~DirectionLight(){

}
void DirectionLight::OnUpdateDirection(glm::vec3 direction){
	m_Direction = direction;
}
void DirectionLight::OnRender(std::vector<Shader*>& shaders){
	for(auto shader : shaders) {
		shader->Bind();
		shader->SetUniformVec3f("u_Light.direction",m_Direction);
	}
	Light::OnRender(shaders);
}

void DirectionLight::OnImGuiRender(){
	ImGui::SliderFloat3("Direction ", &m_Direction.x, 0.0f, 1.0f);
	Light::OnImGuiRender();
}

LightList::LightList():Light(){}
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