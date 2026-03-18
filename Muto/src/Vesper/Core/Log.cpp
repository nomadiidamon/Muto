#include "vzpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

/// @file Log.cpp
/// @author Damon S. Green II
/// @brief Implements the logging system for the Vesper engine.
/// @see Log.h

namespace Vesper {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("VESPER");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
	


}