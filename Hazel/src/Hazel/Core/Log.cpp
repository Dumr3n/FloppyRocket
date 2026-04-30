#include "hzpch.h"
#include "Hazel/Core/Log.h"


namespace Hazel {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		
		s_CoreLogger = spdlog::stdout_logger_mt("HAZEL");
		s_ClientLogger = spdlog::stdout_logger_mt("APP");


		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}