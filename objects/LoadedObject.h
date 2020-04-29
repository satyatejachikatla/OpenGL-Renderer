#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <Object.h>
#include <LoadSaveObj.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace objects {

	class LoadedObject : public  Object{
		private:

			std::shared_ptr<LoadedObjectData> m_Data;

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Texture> m_Texture;

			Renderer m_Renderer;

		public:
			std::unique_ptr<Shader> m_Shader;

			LoadedObject(const char* objfile,const char* texfile);
			~LoadedObject();

			void OnUpdate() override;
			void OnRender() override;
			void OnImGuiRender() override;
			
	};
}