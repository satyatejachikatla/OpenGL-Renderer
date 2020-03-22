#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace material {

	class Box {
		private:
			Vertex m_Vertices[24];

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Texture> m_Texture;

			Renderer m_Renderer;
			
			glm::vec3 m_Rotate;
			glm::vec3 m_Scale;
			glm::vec3 m_Translate;

			glm::mat4 m_Model;

		public:
			Box(char* img);
			~Box();

			void OnUpdate();
			void OnRender();
			void OnImGuiRender();
			
	};
}