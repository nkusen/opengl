#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

using namespace std;

struct ShaderProgramSource {
	string vertexSource;
	string fragmentSource;
};

class Shader {
private:
	string m_Filepath;
	unsigned int m_RendererID;
	unordered_map <string, int> m_UniformLocationCache;
public:
	Shader(const string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const string& mane, int value);
	void setUniform1f(const string& mane, float value);
	void setUniform4f(const string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const string& name, glm::mat4& matrix);
private:
	ShaderProgramSource parseShader(const string& filepath);
	unsigned int compileShader(unsigned int type, const string& source);
	unsigned int createShader(const string& vertexShader, const string& fragmentShader);
	int getUniformLocation(const string& name);
};