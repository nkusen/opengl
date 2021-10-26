#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void*)offset));
		offset += VertexBufferElement::getSizeOfType(element.type) * element.count;
	}
}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const {
	GLCall(glBindVertexArray(0));
}
