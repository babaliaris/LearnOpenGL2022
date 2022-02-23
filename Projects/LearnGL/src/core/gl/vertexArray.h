#pragma once
#include "vertexBuffer.h"

namespace LearnOpenGL
{
	class VertexArray
	{

	public:
		VertexArray(VertexBuffer& vbo);
		~VertexArray();

		void bind();
		void unBind();

	private:
		unsigned int m_id;

	};
}
