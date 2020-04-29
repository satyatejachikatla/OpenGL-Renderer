#pragma once

#include <Test.h>
#include <Lighting.h>
#include <LoadedObject.h>

#include <memory>

namespace test {
	class TestLoadingObj : public Test {
		public:
			TestLoadingObj();
			~TestLoadingObj();

			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;

		private:

			objects::LoadedObject m_Obj;
			Camera m_Camera;

			std::vector<Shader*> shader_list;
			light::LightList m_LightList;


	};
}
