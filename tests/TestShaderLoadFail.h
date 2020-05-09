#pragma once

#include <Test.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <memory>

namespace test {
	class TestShaderLoadFail : public Test {
		public:
			TestShaderLoadFail();
			~TestShaderLoadFail();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:
			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<VertexBuffer> m_VBO;
			std::unique_ptr<Texture> m_Texture[5];

			glm::mat4 m_Proj;

			Renderer m_Renderer;

			GLFWwindow* window;
			int width, height;


			std::string shader_name;
			std::string texture_name[5];
	};
}
