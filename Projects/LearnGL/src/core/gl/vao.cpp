#include "pch.h"
#include "vao.h"
#include <core/gl/glcall.h>
#include <glad/glad.h>

LearnOpenGL::Vao::Vao() : m_id(0)
{
	GLCall(glGenVertexArrays(1, &m_id));
}

LearnOpenGL::Vao::~Vao()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void LearnOpenGL::Vao::Bind()
{
	GLCall(glBindVertexArray(m_id));
}

void LearnOpenGL::Vao::Ubind()
{
	GLCall(glBindVertexArray(0));
}
