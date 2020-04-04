#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace material {

	class Material {
		private:
			static unsigned int m_MaterialId_Count;
			static unsigned int m_MaterialId_CurrCount;

		protected:
			unsigned int m_MaterialId;
			glm::mat4 m_Model;

			glm::vec3 m_Rotate;
			glm::vec3 m_Scale;
			glm::vec3 m_Translate;

		public:
			Material();
			~Material();

			virtual void OnUpdate();
			virtual glm::mat4 OnRender();
			virtual void OnImGuiRender();
			
	};
}