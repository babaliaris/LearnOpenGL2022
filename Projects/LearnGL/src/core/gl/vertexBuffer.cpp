#include "pch.h"
#include "vertexBuffer.h"
#include <core/gl/glcall.h>
#include <glad/glad.h>

LearnOpenGL::VertexBuffer::VertexBuffer(const void* data, unsigned int size) : m_id(0), m_stride(0), m_bufferSize(size), m_vertexCount(0)
{
	GLCall(glGenBuffers(1, &m_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

LearnOpenGL::VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void LearnOpenGL::VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void LearnOpenGL::VertexBuffer::unBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
