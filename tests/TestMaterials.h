#pragma once

#include <Test.h>
#include <Box.h>
#include <Plane.h>

#include <memory>

namespace test {
	class TestMaterials : public Test {
		public:
			TestMaterials();
			~TestMaterials();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			material::Box m_Box;
			material::Box m_Box_refrence;
			material::Plane m_Plane;
			Camera m_Camera;


	};
}
