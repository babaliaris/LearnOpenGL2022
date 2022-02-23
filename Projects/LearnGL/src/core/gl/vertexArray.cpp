#include "pch.h"
#include "vertexArray.h"
#include <core/gl/glcall.h>
#include <glad/glad.h>
#include <core/logger.h>


namespace LearnOpenGL
{
	GLenum GetOpenGLType(LayoutTypeE type)
	{
		switch (type)
		{
		case LearnOpenGL::LayoutTypeE::FLOAT:
			return GL_FLOAT;

		default:
			LEARN_OPENGL_ERROR("This should not have happened.");
			GL_NONE;
		}
	}
}

LearnOpenGL::VertexArray::VertexArray(VertexBuffer& vbo) : m_id(0)
{
	//Generate and Bind VAO.
	GLCall(glGenVertexArrays(1, &m_id));
	GLCall(glBindVertexArray(m_id));

	//Bind VBO.
	vbo.bind();

	//Get the layouts of VBO.
	const std::vector<BufferLayout>& layouts = vbo.getLayouts();

	//Enable the Vertex Attributes.
	unsigned int offset = 0;
	for (int index = 0; index < layouts.size(); index++)
	{
		//Get the normalized in a GLenum.
		GLenum normalized = layouts[index].normalized ? GL_TRUE : GL_FALSE;

		//Define the vertex attribute.
		GLCall(glVertexAttribPointer(index, layouts[index].count, GetOpenGLType(layouts[index].type), normalized, vbo.getStride(), (const void*)offset));

		//Enable the vertex attribute.
		GLCall(glEnableVertexAttribArray(index));

		//Log some info.
		LEARN_OPENGL_INFO("{}: index: {}, count: {}, typeSize: {}, norm: {}, stride: {}, offset: {}", layouts[index].name, index, 
			layouts[index].count, layouts[index].typeSize, normalized, vbo.getStride(), offset);

		//Increase the offset.
		offset += layouts[index].typeSize * layouts[index].count;
	}

	//Calcualate the count of the vertices.
	vbo.m_vertexCount = vbo.m_bufferSize / vbo.getStride();

	//Log the verticies count.
	LEARN_OPENGL_INFO("Vertices: {}", vbo.m_vertexCount);

	//Unbind VAO and then VBO.
	GLCall(glBindVertexArray(0));
	vbo.unBind();
}

LearnOpenGL::VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_id));
}

void LearnOpenGL::VertexArray::bind()
{
	GLCall(glBindVertexArray(m_id));
}

void LearnOpenGL::VertexArray::unBind()
{
	GLCall(glBindVertexArray(0));
}
