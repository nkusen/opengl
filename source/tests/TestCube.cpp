#include "TestCube.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace test {

	TestCube::TestCube() 
		: m_VA{}, m_VB{ nullptr }, m_Layout{}, m_IB{ nullptr }, m_Shader{ "res/shaders/Color.shader" },
		model{ 1.0f }, view{ glm::lookAt(
								glm::vec3(0, 0, 12),
								glm::vec3(0, 0, 0),
								glm::vec3(0, 1, 0))}, 
		proj{ glm::perspective(glm::radians(45.0f), 1.33f, 0.1f, 100.0f) }, translation{ 0.0f }, scale{ 1.0f },
		rotation{0.0f, 0.0f, 0.0f}, m_Color{ 0.0f, 0.0f, 0.0f, 1.0f } {

		float positions[] = {
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 0, 3, 2,
			4, 5, 6, 4, 7, 6,
			7, 4, 0, 7, 3, 0,
			6, 2, 1, 6, 5, 1,
			0, 1, 5, 0, 4, 5,
			2, 3, 7, 2, 6, 7
		};

		m_VB = new VertexBuffer(positions, 8 * 7 * sizeof(float));
		m_IB = new IndexBuffer(indices, 36);

		m_Layout.push<float>(3);
		m_Layout.push<float>(4);
		m_VA.addBuffer(*m_VB, m_Layout);

		m_Shader.bind();
		m_Shader.setUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

	}

	TestCube::~TestCube() {
		delete m_VB;
		delete m_IB;
		glDisable(GL_DEPTH_TEST);
	}

	void TestCube::onUpdate(float detaTime) {
		glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(glm::mat4(1.0f), translation) * rotZ * rotY * rotX * glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	}

	void TestCube::onRender(Renderer& renderer) {

		GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Shader.bind();
		glm::mat4 MVP = proj * view * model;
		m_Shader.setUniformMat4f("u_MVP", MVP);
		m_VA.bind(); m_IB->bind();

		GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));

		/*
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int) * 6 * 0)));

		color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int) * 6 * 1)));

		color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int) * 6 * 2)));

		color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int) * 6 * 3)));

		color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int)*  6 * 4)));

		color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f;
		m_Shader.setUniform4f("u_Color", color[0], color[1], color[2], color[3]);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)(sizeof(unsigned int) * 6 * 5)));
		*/
	}

	void TestCube::onImGuiRender() {
		ImGui::SliderFloat("Position X:", &translation.x, -2.0f,  2.0f);
		ImGui::SliderFloat("Position Y:", &translation.y, -2.0f,  2.0f);
		ImGui::SliderFloat("Position Z:", &translation.z, -30.0f, 3.0f);
		ImGui::SliderFloat("Scale:", &scale, 0.0f, 10.0f);
		ImGui::SliderFloat3("Rotation:", rotation, -180.0f, 180.0f);
		ImGui::ColorEdit4("Color", m_Color);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}