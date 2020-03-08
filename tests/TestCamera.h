#pragma once

#include <Test.h>


#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>

#include <memory>

namespace test {
	class TestCamera : public Test {
		public:
			TestCamera();
			~TestCamera();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Texture> m_Texture;

			Camera m_Camera;


	};
}
