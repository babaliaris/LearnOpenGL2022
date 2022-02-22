#pragma once
#include <iostream>

namespace LearnOpenGL
{
	class Shader
	{

	public:

		Shader(const std::string& shader_path);
		~Shader();

		void Bind();
		void Unbind();

		inline bool IsValid() { return m_isValid; }



	private:
		unsigned int m_id;
		bool m_isValid;
	};
}
