#pragma once

#include "Test.h"

#include "Renderer.h"

namespace test {

	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender(Renderer& renderer) override;
		void onImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

}
