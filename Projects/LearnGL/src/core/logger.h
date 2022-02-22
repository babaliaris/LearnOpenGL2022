#pragma once
#include <memory>
#include <spdlog/spdlog.h>


namespace LearnOpenGL
{
	class Logger
	{

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetLogger() { return m_logger; }

	private:
		static std::shared_ptr<spdlog::logger> m_logger;

	};
}



#ifdef LEARN_OPENGL_DEBUG

#define LEARN_OPENGL_INFO(spdl_format, ...)\
	LearnOpenGL::Logger::GetLogger()->info(spdl_format, __VA_ARGS__)

#define LEARN_OPENGL_WARN(spdl_format, ...)\
	LearnOpenGL::Logger::GetLogger()->warn(spdl_format, __VA_ARGS__)

#define LEARN_OPENGL_ERROR(spdl_format, ...)\
	LearnOpenGL::Logger::GetLogger()->error(spdl_format, __VA_ARGS__)

#endif