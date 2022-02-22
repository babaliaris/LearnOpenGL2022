#include "pch.h"
#include "vbo.h"
#include <core/logger.h>
#include <core/gl/glcall.h>
#include <glad/glad.h>


GLenum GetOpenGLType(LearnOpenGL::LayoutTypeE type)
{
	switch (type)
	{
	case LearnOpenGL::LayoutTypeE::FLOAT:
		return GL_FLOAT;

	default:
		GL_NONE;
	}
}



unsigned int GetOpenGLTypeSize(LearnOpenGL::LayoutTypeE type)
{
	switch (type)
	{
	case LearnOpenGL::LayoutTypeE::FLOAT:
		return sizeof(GLfloat);

	default:
		0;
	}
}


LearnOpenGL::Vbo::Vbo(float* data, unsigned int count) : m_id(0), m_index(0), m_offset(0)
{
	//Generate the buffer.
	GLCall(glGenBuffers(1, &m_id));

	//Bind it.
	Bind();

	//Allocate memory and transfer the data.
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_STATIC_DRAW));

	//Unbind.
	Unbind();
}

LearnOpenGL::Vbo::~Vbo()
{
	GLCall(glDeleteBuffers(1, &m_id));
}

void LearnOpenGL::Vbo::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void LearnOpenGL::Vbo::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void LearnOpenGL::Vbo::PushLayout(BufferLayout layout)
{
	LEARN_OPENGL_INFO("Index: {}, Size: {}, TypeSize: {}, Normalize: {}, Stride: {}, Offset: {}.", m_index, layout.size, GetOpenGLTypeSize(layout.type),
		GL_FALSE, layout.stride, m_offset);

	//Specify the attribute.
	GLCall(glVertexAttribPointer(m_index, layout.size, GetOpenGLType(layout.type), GL_FALSE, layout.stride, (const void*)m_offset));

	//Enable it.
	GLCall(glEnableVertexAttribArray(m_index));

	//Increase the offset.
	m_offset += GetOpenGLTypeSize(layout.type) * layout.size;

	//increase the index.
	m_index++;
}
