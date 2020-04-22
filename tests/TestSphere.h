#pragma once

#include <Test.h>
#include <Sphere.h>

#include <memory>

namespace test {
	class TestSphere : public Test {
		public:
			TestSphere();
			~TestSphere();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			objects::Sphere m_Sphere;
			Camera m_Camera;

			std::vector<Shader*> shader_list;
			light::LightList m_LightList;


	};
}
