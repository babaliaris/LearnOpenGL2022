#pragma once
#include <iostream>

namespace LearnOpenGL
{
	class Texture
	{

	public:
		Texture(const std::string& path);
		~Texture();

		void bind(int slot = 0);
		void unBind();

		inline int getWidth() { return m_width; }
		inline int getHeight() { return m_height; }

	private:
		unsigned int m_id;
		int m_width, m_height, m_channels;
		std::string m_path;

	};
}
