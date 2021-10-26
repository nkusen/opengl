#include "TestMovingLogoBG.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace test {

	TestMovingLogoBG::TestMovingLogoBG() 
		:   positions{
			-150.0f, -100.0f, 0.0f, 0.0f,
			 150.0f, -100.0f, 1.0f, 0.0f,
			 150.0f,  100.0f, 1.0f, 1.0f,
			-150.0f,  100.0f, 0.0f, 1.0f},
		    indices{
			 0, 1, 2,
			 2, 3, 0},
			va{}, vb{ positions, 4 * 4 * sizeof(float) },
			layout{}, ib{indices, 6},
			proj{ glm::ortho(0.0f, 640.0f, 0.0f, 480.0f) }, view{1.0f}, colorModel{1.0f}, textureModelA{1.0f}, textureModelB{1.0f},
			colorShader{ "res/shaders/Color.shader" }, textureShader{ "res/shaders/Texture.shader" }, texture{ "res/textures/cpp.png" },
			translationColor{1.0f}, translationA{1.0f}, translationB{1.0f}, r{0.0f}, increment{0.05f} {

		layout.push<float>(2);
		layout.push<float>(2);
		va.addBuffer(vb, layout);

		textureShader.bind();
		texture.bind();
		textureShader.setUniform1i("u_Texture", 0);
	}

	TestMovingLogoBG::~TestMovingLogoBG() {

	}

	void TestMovingLogoBG::onUpdate(float deltaTime) {
		colorModel = glm::translate(glm::mat4(1.0f), translationColor);
		textureModelA = glm::translate(glm::mat4(1.0f), translationA);
		textureModelB = glm::translate(glm::mat4(1.0f), translationB);

		r += increment;
		if (r < 0.0f || r > 1.0f) increment *= -1;
	}

	void TestMovingLogoBG::onRender(Renderer& renderer) {

		colorShader.bind();
		{
			colorShader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			glm::mat4 MVP = proj * view * colorModel;
			colorShader.setUniformMat4f("u_MVP", MVP);
			renderer.draw(va, ib, colorShader);
		}


		textureShader.bind();
		{
			glm::mat4 MVP = proj * view * textureModelA;
			textureShader.setUniformMat4f("u_MVP", MVP);
			renderer.draw(va, ib, textureShader);
		}
		{
			glm::mat4 MVP = proj * view * textureModelB;
			textureShader.setUniformMat4f("u_MVP", MVP);
			renderer.draw(va, ib, textureShader);
		}

	}

	void TestMovingLogoBG::onImGuiRender() {
		ImGui::SliderFloat3("Color", &translationColor.x, 0.0f, 640.0f);
		ImGui::SliderFloat3("A", &translationA.x, 0.0f, 640.0f);
		ImGui::SliderFloat3("B", &translationB.x, 0.0f, 640.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
