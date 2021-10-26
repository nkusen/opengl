#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	class TestMovingLogoBG : public Test {
	public:
		TestMovingLogoBG();
		~TestMovingLogoBG();

		void onUpdate(float deltaTime) override;
		void onRender(Renderer& renderer) override;
		void onImGuiRender() override;
	private:
		float positions[16];
		unsigned int indices[6];
		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;

		glm::mat4 proj;
		glm::mat4 view;
		glm::mat4 colorModel;
		glm::mat4 textureModelA;
		glm::mat4 textureModelB;

		Shader colorShader;
		Shader textureShader;
		Texture texture;

		glm::vec3 translationColor;
		glm::vec3 translationA;
		glm::vec3 translationB;

		float r;
		float increment;
	};

}
