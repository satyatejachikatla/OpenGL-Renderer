#pragma once

#include <Test.h>
#include <Box.h>
#include <Plane.h>

#include <memory>

namespace test {
	class TestObjects : public Test {
		public:
			TestObjects();
			~TestObjects();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			objects::Box m_Box;
			objects::Box m_Box_refrence;
			objects::Plane m_Plane;
			Camera m_Camera;

			light::LightList m_LightList;
			std::vector<Shader*> shader_list;

	};
}
