#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <Material.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace material {

	class Box : public  Material{
		private:

			Vertex m_Vertices[24];

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Texture> m_Texture;

			Renderer m_Renderer;

		public:
			Box(char* img);
			~Box();

			void OnUpdate() override;
			glm::mat4 OnRender() override;
			void OnImGuiRender() override;
			
	};
}