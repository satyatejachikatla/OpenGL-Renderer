#include "glErrors.h"
#include "VertexBuffer.h"
#include <GL/glew.h>


VertexBuffer::VertexBuffer(const void* data,unsigned int size) : m_Size(size){
	glCall(glGenBuffers(1,&m_RendererID));
	glCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
	glCall(glBufferData(GL_ARRAY_BUFFER,m_Size,data,GL_DYNAMIC_DRAW));

}
VertexBuffer::~VertexBuffer() {
	glCall(glDeleteBuffers(1,&m_RendererID));
}

void VertexBuffer::Bind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
}

void VertexBuffer::Bind(const void* data) const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));
	glCall(glBufferSubData(GL_ARRAY_BUFFER,0,m_Size,data));
}

void VertexBuffer::Unbind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}