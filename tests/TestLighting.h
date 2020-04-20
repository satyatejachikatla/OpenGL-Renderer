#pragma once

#include <Test.h>
#include <Box.h>
#include <Plane.h>
#include <Lighting.h>

#include <memory>

namespace test {
	class TestLighting : public Test {
		public:
			TestLighting();
			~TestLighting();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			objects::ObjectList m_Boxs;
			light::LightList m_LightList;
			std::shared_ptr<light::SpotLight> splight;
			std::vector<Shader*> shader_list;

			Camera m_Camera;
	};
}
