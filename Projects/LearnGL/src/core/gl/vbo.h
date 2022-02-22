#pragma once
#include <vector>

namespace LearnOpenGL
{

	enum class LayoutTypeE
	{
		FLOAT
	};

	struct BufferLayout
	{
		int size;
		int stride;
		LayoutTypeE type;
	};

	class Vbo
	{
	public:
		Vbo(float* data, unsigned int count);
		~Vbo();

		void Bind();
		void Unbind();

		void PushLayout(BufferLayout layout);

	private:
		unsigned int m_id, m_index, m_offset;
		std::vector<BufferLayout> m_layouts;

	};
}
