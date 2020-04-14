#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace objects {

	class Object {
		private:
			static unsigned int m_Object_Count;
			static unsigned int m_Object_CurrCount;

		protected:
			unsigned int m_ObjectId;
			glm::mat4 m_Model;

			glm::vec3 m_Rotate;
			glm::vec3 m_Scale;
			glm::vec3 m_Translate;

		public:
			Object();
			~Object();

			unsigned int  getObjectId() const{return m_ObjectId;}
			virtual void OnUpdate();
			virtual void OnRender();
			virtual void OnImGuiRender();
			
	};

	class ObjectList :  Object{
		public:
			std::vector<std::shared_ptr<Object>>  m_Objects;

			ObjectList();
			~ObjectList();

			void OnUpdate();
			void OnRender();
			void OnImGuiRender();
			
	};
}