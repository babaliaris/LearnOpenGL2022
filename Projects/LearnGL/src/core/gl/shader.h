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

		void setInt(const std::string& uniform_name, int value);

		inline bool IsValid() { return m_isValid; }



	private:
		unsigned int m_id;
		bool m_isValid;
	};
}
