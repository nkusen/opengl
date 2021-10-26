#include "Renderer.h"
#include <iostream>

using namespace std;

void GLClearError() {
    while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        cout << error << ' ' << function << " < " << file << " : " << line << endl;
        return false;
    }
    return true;
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
    shader.bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
