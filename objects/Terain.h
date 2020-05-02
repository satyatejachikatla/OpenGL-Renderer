#pragma once

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <Object.h>

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace objects {

	class Terain : public  Object{
		private:

			std::vector<Vertex> m_Vertices;

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Texture> m_Texture;

			Renderer m_Renderer;

		public:

			std::unique_ptr<Shader> m_Shader;

			Terain(const char* img);
			~Terain();

			void OnUpdate() override;
			void OnRender() override;
			void OnImGuiRender() override;
			
	};
}