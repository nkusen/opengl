#pragma once

#include <vector>
#include "Renderer.h"

using namespace std;

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalised;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	vector <VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {};

	template <typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template <>
	void push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template <>
	void push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template <>
	void push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};