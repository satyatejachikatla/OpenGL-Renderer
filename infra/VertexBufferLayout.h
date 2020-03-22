#pragma once

#include <glErrors.h>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT : 		return sizeof(GLfloat);
		case GL_UNSIGNED_INT :	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE :	return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

template<typename T>
struct identity { typedef T type; };

struct Vertex {
	glm::vec3 vertexCoords;
	glm::vec3 color;
	glm::vec2 textureCoords;
	float textureId;
};

class VertexBufferLayout {
	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;

		template<typename T>
		void Push(unsigned int count,identity<T> _) {
			//static_assert(false);
			std::cerr << __PRETTY_FUNCTION__ << std::endl;
			ASSERT(false);
		}

		void Push(unsigned int count,identity<float> _) {
			m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
			m_Stride += count*VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}

		void Push(unsigned int count,identity<unsigned int> _) {
			m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
			m_Stride += count*VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		void Push(unsigned int count,identity<unsigned char> _) {
			m_Elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
			m_Stride += count*VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}
		void Push(unsigned int count,identity<glm::vec3> _) {
			m_Elements.push_back({GL_FLOAT,count*3,GL_FALSE});
			m_Stride += count*VertexBufferElement::GetSizeOfType(GL_FLOAT)*3;
		}

		void Push(unsigned int count,identity<glm::vec2> _) {
			m_Elements.push_back({GL_FLOAT,count*2,GL_FALSE});
			m_Stride += count*VertexBufferElement::GetSizeOfType(GL_FLOAT)*2;
		}



	public:
		VertexBufferLayout() : m_Stride(0) {}
		~VertexBufferLayout() {}

		template <typename TL>
		void Push(unsigned int count) {
			Push(count,identity<TL>());
		}

	
	inline const std::vector<VertexBufferElement>& GetElements() const {return m_Elements;}
	inline unsigned int GetStride() const {return m_Stride;}


	void VertexLayoutAutoFill(){
		Push<glm::vec3>(1);
		Push<glm::vec3>(1);
		Push<glm::vec2>(1);
		Push<float>(1);
	}
};
