#pragma once
#include <iostream>
#include <vector>
#include <core/logger.h>

namespace LearnOpenGL
{

	enum class LayoutTypeE
	{
		FLOAT
	};

	struct BufferLayout
	{
		unsigned int count;
		unsigned int typeSize;
		bool normalized;
		LayoutTypeE type;
		std::string name;
	};

	class VertexBuffer
	{
		friend class VertexArray;

	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		//Bind and Unbind methods.
		void bind() const;
		void unBind() const;
		
		//Get Vertex Count.
		inline unsigned int getVertexCount() const { return m_vertexCount; }

		//Get the layouts array.
		inline const std::vector<BufferLayout>& getLayouts() const { return m_layouts; }

		//Get the stride of the vertex.
		inline unsigned int getStride() const { return m_stride; }

		//Unsupported type.
		template<typename T>
		void pushLayout(unsigned int size, bool normalized, const std::string& name)
		{
			LEARN_OPENGL_WARN("Somewhere in your code you are calling VertexBuffer::pushLayout<T> with an unsupported type T.");
		}

		//Push a Layout.
		template<>
		void pushLayout<float>(unsigned int count, bool normalized, const std::string& name)
		{
			m_layouts.push_back({ count, sizeof(float), normalized, LayoutTypeE::FLOAT, name });
			m_stride += sizeof(float) * count;
		}

	private:
		unsigned int m_id, m_stride, m_bufferSize, m_vertexCount;
		std::vector<BufferLayout> m_layouts;
	};
}

