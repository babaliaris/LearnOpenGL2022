#pragma once
#include <memory>
#include <spdlog/spdlog.h>


namespace LearnOpenGL
{
	class Logger
	{

	public:
		static void Init();

		static std::string AddFileLine(const std::string& fmt, const char* file, unsigned int line);

		inline static std::shared_ptr<spdlog::logger> GetLogger() { return m_logger; }

	private:
		static std::shared_ptr<spdlog::logger> m_logger;

	};
}



#ifdef LEARN_OPENGL_DEBUG

	#define LEARN_OPENGL_INFO(fmt, ...)\
		LearnOpenGL::Logger::GetLogger()->info(fmt, __VA_ARGS__)

	#define LEARN_OPENGL_WARN(fmt, ...)\
		LearnOpenGL::Logger::GetLogger()->warn(fmt, __VA_ARGS__)

	#define LEARN_OPENGL_ERROR(fmt, ...)\
		LearnOpenGL::Logger::GetLogger()->error(LearnOpenGL::Logger::AddFileLine(fmt, __FILE__, __LINE__), __VA_ARGS__)

#endif