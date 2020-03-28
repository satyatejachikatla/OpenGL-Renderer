#include <glErrors.h>
#include <GL/glew.h>
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count)
	: m_Count(count) {
	glCall(glGenBuffers(1,&m_RendererID));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),data,GL_DYNAMIC_DRAW));

}
IndexBuffer::~IndexBuffer() {
	glCall(glDeleteBuffers(1,&m_RendererID));
}

void IndexBuffer::Bind(unsigned int* data) const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
	glCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,m_Count*sizeof(unsigned int),data));
}

void IndexBuffer::Bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
}

void IndexBuffer::Unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}