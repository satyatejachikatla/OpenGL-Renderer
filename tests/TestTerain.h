#pragma once

#include <Test.h>
#include <Terain.h>

#include <memory>

namespace test {
	class TestTerain : public Test {
		public:
			TestTerain();
			~TestTerain();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			objects::Terain m_Terain;
			Camera m_Camera;

			std::vector<Shader*> shader_list;
			light::LightList m_LightList;


	};
}
