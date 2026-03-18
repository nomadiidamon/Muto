#pragma once
/// @file Log.h
/// @author Damon S. Green II
/// @brief Declares the logging system for the Vesper engine.

#include "Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Vesper {

	/// @class Log
	/// @brief A logging utility class for the Vesper engine.
	/// @todo Rethink logging flow with Macros and possibly implement different loggers for different modules.
	class Log
	{
	public:

		/// @brief Initializes the logging system.
		static void Init();

		/// @brief Returns the core logger instance.
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		/// @brief Returns the client logger instance.
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


}

/// @brief trace: lowest level, for detailed debug information
#define VZ_CORE_TRACE(...)    ::Vesper::Log::GetCoreLogger()->trace(__VA_ARGS__)
/// @brief info: general information about application flow
#define VZ_CORE_INFO(...)     ::Vesper::Log::GetCoreLogger()->info(__VA_ARGS__)
/// @brief warn: indicates a potential issue or important event
#define VZ_CORE_WARN(...)     ::Vesper::Log::GetCoreLogger()->warn(__VA_ARGS__)
/// @brief error: indicates an error that has occurred
#define VZ_CORE_ERROR(...)    ::Vesper::Log::GetCoreLogger()->error(__VA_ARGS__)
/// @brief fatal: indicates a critical error that may cause application termination
#define VZ_CORE_FATAL(...)    ::Vesper::Log::GetCoreLogger()->critical(__VA_ARGS__)

/// @brief trace: lowest level, for detailed debug information
#define VZ_TRACE(...)         ::Vesper::Log::GetClientLogger()->trace(__VA_ARGS__)
/// @brief info: general information about application flow
#define VZ_INFO(...)          ::Vesper::Log::GetClientLogger()->info(__VA_ARGS__)
/// @brief warn: indicates a potential issue or important event
#define VZ_WARN(...)          ::Vesper::Log::GetClientLogger()->warn(__VA_ARGS__)
/// @brief error: indicates an error that has occurred
#define VZ_ERROR(...)         ::Vesper::Log::GetClientLogger()->error(__VA_ARGS__)
/// @brief fatal: indicates a critical error that may cause application termination
#define VZ_FATAL(...)         ::Vesper::Log::GetClientLogger()->critical(__VA_ARGS__)
