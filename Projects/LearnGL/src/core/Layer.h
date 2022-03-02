#pragma once

namespace LearnOpenGL
{
	class Layer
	{
		friend class App;

	public:
		virtual void OnStart(){}
		virtual void OnUpdate(){}

	private:
		bool m_Started = false;
	};
}