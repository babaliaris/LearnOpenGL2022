#include "pch.h"
#include "logger.h"


namespace LearnOpenGL
{
	//Create the static logger.
	std::shared_ptr<spdlog::logger> Logger::m_logger = spdlog::stdout_color_mt("Logger");


	void Logger::Init()
	{
		m_logger->set_pattern("[%n:%l] %v%$");
	}


	std::string Logger::AddFileLine(const std::string& fmt, const char* file, unsigned int line)
	{
		std::stringstream stream;

		stream << fmt << "\n\tIn File: " << file << "\n\tAt Line: " << line << std::endl << std::endl;

		return stream.str();
	}
}