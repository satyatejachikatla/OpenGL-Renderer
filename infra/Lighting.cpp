#include <Lighting.h>

#include <sstream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace light {
	unsigned int PointLight::m_PointLightIdCount=0;
	unsigned int DirectionLight::m_DirectionLightIdCount=0;
	unsigned int SpotLight::m_SpotLightIdCount=0;

	std::unordered_set <unsigned int> PointLight::m_PointLightIdAssigned;
	std::unordered_set <unsigned int> DirectionLight::m_DirectionLightIdAssigned;
	std::unordered_set <unsigned int> SpotLight::m_SpotLightIdAssigned;

	/*-----------------------------------------------------------------------------------------------------*/
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
		std::string uniformName = getUniformName();

		for(auto shader : shaders) {
			shader->Bind();
			shader->SetUniformVec3f((uniformName+std::string(".ambient").c_str()),m_Color*m_Ambient);
			shader->SetUniformVec3f((uniformName+std::string(".diffuse").c_str()),m_Color*m_Diffuse);
			shader->SetUniformVec3f((uniformName+std::string(".specular").c_str()),m_Color*m_Specular);
		}
	}
	void Light::OnImGuiRender(){
		ImGui::SliderFloat3("Ambient ", &m_Ambient.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse ", &m_Diffuse.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular ", &m_Specular.x, 0.0f, 1.0f);
	}

	/*-----------------------------------------------------------------------------------------------------*/

	PointLight::PointLight(glm::vec3 Position,glm::vec3 Color) 
		: m_Position(Position),
		  m_AttenuationQuadraticCoefficients(glm::vec3(0.0f,0.0f,1.0f)), 
		  Light(Color) {
			for(int i=0;i<=m_PointLightIdCount;i++){
				if(m_PointLightIdAssigned.find(i) == m_PointLightIdAssigned.end()){
					m_PointLightId = i;
					m_PointLightIdAssigned.insert(i);
					break;
				}
			}
			ASSERT(m_PointLightIdAssigned.find(m_PointLightId) != m_PointLightIdAssigned.end());
			m_PointLightIdCount+=1;

	}
	PointLight::~PointLight(){
		m_PointLightIdCount-=1;
		m_PointLightIdAssigned.erase(m_PointLightIdAssigned.find(m_PointLightId));
	}
	void PointLight::OnUpdatePosition(glm::vec3 pos_or_speed,bool is_pos){
		if(is_pos) {
			m_Position = pos_or_speed; 
		} else {
			m_Position += pos_or_speed;
		}
	}
	void PointLight::OnRender(std::vector<Shader*>& shaders){
		std::string uniformName = getUniformName();
		for(auto shader : shaders) {
			shader->Bind();
			shader->SetUniformVec3f((uniformName+std::string(".position").c_str()),m_Position);
			shader->SetUniformVec3f((uniformName+std::string(".attenuationQuadraticEquation").c_str()),m_AttenuationQuadraticCoefficients);
		}
		Light::OnRender(shaders);
	}
	void PointLight::OnUpdateAttenuation(glm::vec3 attenuationQuadraticCoefficients){
		m_AttenuationQuadraticCoefficients = attenuationQuadraticCoefficients;
	}
	void PointLight::OnImGuiRender(){
		ImGui::SliderFloat3("Position ", &m_Position.x, 0.0f, 1.0f);
		Light::OnImGuiRender();
	}
	std::string PointLight::getUniformName(){
		std::stringstream uniformName;
		uniformName << "u_PointLight["<<m_PointLightId<<"]";
		return uniformName.str();
	}
	unsigned int PointLight::getLightCount(){
		return m_PointLightIdCount;
	}

	/*-----------------------------------------------------------------------------------------------------*/

	DirectionLight::DirectionLight(glm::vec3 Direction,glm::vec3 Color) 
		:	m_Direction(Direction),
			Light(Color) {
			for(int i=0;i<=m_DirectionLightIdCount;i++){
				if(m_DirectionLightIdAssigned.find(i) == m_DirectionLightIdAssigned.end()){
					m_DirectionLightId = i;
					m_DirectionLightIdAssigned.insert(i);
					break;
				}
			}
			ASSERT(m_DirectionLightIdAssigned.find(m_DirectionLightId) != m_DirectionLightIdAssigned.end());
			m_DirectionLightIdCount+=1;
	}
	DirectionLight::~DirectionLight(){
		m_DirectionLightIdCount-=1;
		m_DirectionLightIdAssigned.erase(m_DirectionLightIdAssigned.find(m_DirectionLightId));
	}
	void DirectionLight::OnUpdateDirection(glm::vec3 direction){
		m_Direction = direction;
	}
	void DirectionLight::OnRender(std::vector<Shader*>& shaders){
		std::string uniformName = getUniformName();
		for(auto shader : shaders) {
			shader->Bind();
			shader->SetUniformVec3f((uniformName+std::string(".direction").c_str()),m_Direction);
		}
		Light::OnRender(shaders);
	}

	void DirectionLight::OnImGuiRender(){
		ImGui::SliderFloat3("Direction ", &m_Direction.x, 0.0f, 1.0f);
		Light::OnImGuiRender();
	}
	std::string DirectionLight::getUniformName(){
		std::stringstream uniformName;
		uniformName << "u_DirectionLight["<<m_DirectionLightId<<"]";
		return uniformName.str();
	}
	unsigned int DirectionLight::getLightCount(){
		return m_DirectionLightIdCount;
	}

	/*-----------------------------------------------------------------------------------------------------*/

	SpotLight::SpotLight(glm::vec3 Position,glm::vec3 Direction,glm::vec3 Color)
		:	m_Position(Position),
			m_Direction(Direction),
			m_CutOff(glm::cos(glm::radians(12.5f))),
			m_OuterCutOff(glm::cos(glm::radians(15.0f))),
			Light(Color){

			for(int i=0;i<=m_SpotLightIdCount;i++){
				if(m_SpotLightIdAssigned.find(i) == m_SpotLightIdAssigned.end()){
					m_SpotLightId = i;
					m_SpotLightIdAssigned.insert(i);
					break;
				}
			}
			ASSERT(m_SpotLightIdAssigned.find(m_SpotLightIdCount) != m_SpotLightIdAssigned.end());
			m_SpotLightIdCount+=1;

	}
	SpotLight::~SpotLight(){
		m_SpotLightIdCount-=1;
		m_SpotLightIdAssigned.erase(m_SpotLightIdAssigned.find(m_SpotLightId));
	}

	std::string SpotLight::getUniformName(){
		std::stringstream uniformName;
		uniformName << "u_SpotLightCount["<<m_SpotLightId<<"]";
		return uniformName.str();
	}

	void SpotLight::OnUpdatePosition(glm::vec3 pos_or_speed,bool is_pos){
		if(is_pos) {
			m_Position = pos_or_speed; 
		} else {
			m_Position += pos_or_speed;
		}
	}
	void SpotLight::OnUpdateAttenuation(glm::vec3 attenuationQuadraticCoefficients){
		m_AttenuationQuadraticCoefficients = attenuationQuadraticCoefficients;
	}
	void SpotLight::OnUpdateDirection(glm::vec3 direction){
		m_Direction = direction;
	}

	void SpotLight::OnRender(std::vector<Shader*>& shaders){
		std::string uniformName = getUniformName();
		for(auto shader : shaders) {
			shader->Bind();
			shader->SetUniformVec3f((uniformName+std::string(".direction").c_str()),m_Direction);
			shader->SetUniformVec3f((uniformName+std::string(".position").c_str()),m_Position);
			shader->SetUniformVec3f((uniformName+std::string(".attenuationQuadraticEquation").c_str()),m_AttenuationQuadraticCoefficients);

			shader->SetUniform1f((uniformName+std::string(".cutOff").c_str()),glm::cos(glm::radians(m_CutOff)));
			shader->SetUniform1f((uniformName+std::string(".outerCutOff").c_str()),glm::cos(glm::radians(m_OuterCutOff)));
		}
		Light::OnRender(shaders);
	}

	void SpotLight::OnUpdateCutOffs(float cutOff,float outerCutOff){
		m_CutOff = cutOff;
		m_OuterCutOff = outerCutOff;
	}
	void SpotLight::OnImGuiRender(){
		ImGui::SliderFloat3("Position ", &m_Position.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("Direction ", &m_Direction.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("CutOff ", &m_CutOff, 0.0f, 4.0f);
		ImGui::SliderFloat3("OuterCutOff ", &m_OuterCutOff, 0.0f, 4.0f);
		Light::OnImGuiRender();
	}

	unsigned int SpotLight::getLightCount(){
		return m_SpotLightIdCount;
	}

	/*-----------------------------------------------------------------------------------------------------*/

	LightList::LightList(){}
	LightList::~LightList(){}

	void AssignLightCounts(std::vector<Shader*>& shaders){
		for(auto shader : shaders) {
			shader->Bind();
			shader->SetUniform1f("u_DirectionLightCount",DirectionLight::getLightCount());
			shader->SetUniform1f("u_PointLightCount",PointLight::getLightCount());
			shader->SetUniform1f("u_SpotLightCount",SpotLight::getLightCount());
		}
	}

	void LightList::OnRender(std::vector<Shader*>& shaders){
		for(int i=0;i<m_Lights.size();i++){
			m_Lights[i]->OnRender(shaders);
		}
		AssignLightCounts(shaders);
	}
	void LightList::OnImGuiRender(){
		for(int i=0;i<m_Lights.size();i++){
			m_Lights[i]->OnImGuiRender();
		}
	}
}