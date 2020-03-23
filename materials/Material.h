#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace material {

	class Material {
		private:
			static unsigned int m_MaterialId_Count;

			unsigned int m_MaterialId;

			glm::vec3 m_Rotate;
			glm::vec3 m_Scale;
			glm::vec3 m_Translate;

		protected:
			glm::mat4 m_Model;

		public:
			Material();
			~Material();

			virtual void OnUpdate();
			virtual glm::mat4 OnRender();
			virtual void OnImGuiRender();
			
	};
}