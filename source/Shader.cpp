#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const string& filepath) 
	: m_Filepath(filepath), m_RendererID(0) {
    ShaderProgramSource source = parseShader(filepath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseShader(const string& filepath) {
    ifstream stream(filepath);

    string line;
    stringstream ss[2];
    int type = -1;

    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos)
                type = 0;
            else if (line.find("fragment") != string::npos)
                type = 1;
        }
        else if (type != -1) ss[type] << line << '\n';
    }

    return { ss[0].str(), ss[1].str() };
}

void Shader::bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

unsigned int Shader::compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
        cout << message << endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::setUniform1i(const string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const string& name, glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];


    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) cout << "Warning, uniform doesn't exist: " + name << endl;
    return m_UniformLocationCache[name] = location;
}
