#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	class TestCube : public Test {
	public:
		TestCube();
		~TestCube();

		void onUpdate(float detaTime) override;
		void onRender(Renderer& renderer) override;
		void onImGuiRender() override;
	private:
		VertexArray m_VA;
		VertexBuffer* m_VB;
		VertexBufferLayout m_Layout;
		IndexBuffer* m_IB;
		Shader m_Shader;
		glm::mat4 model, view, proj;
		glm::vec3 translation;
		float scale;
		float rotation[3];
		mutable float m_Color[4];
	};

}
