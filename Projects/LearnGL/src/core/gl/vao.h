#pragma once

namespace LearnOpenGL
{
	class Vao
	{

	public:
		Vao();
		~Vao();

		void Bind();
		void Ubind();


	private:
		unsigned int m_id;

	};
}
