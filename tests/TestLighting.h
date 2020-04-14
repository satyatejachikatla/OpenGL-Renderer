#pragma once

#include <Test.h>
#include <Box.h>
#include <Plane.h>

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

			objects::Box m_Box;
			//objects::Box m_Box_center;

			Camera m_Camera;
	};
}
