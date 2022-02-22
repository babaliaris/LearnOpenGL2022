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
}