
/// @file Instrumentor.h
/// @author TheCherno
/// @author Damon S. Green II
/// @brief Provides instrumentation and profiling utilities.

//Copyright © TheCherno
//Modifications Copyright © 2025 Damon S.Green II(nomad_ii_damon)
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//[Apache](http://www.apache.org/licenses/LICENSE-2.0)

#pragma once

#include "Core/Log.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace Muto {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;


	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		std::mutex m_Mutex;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				// If there is already a current session, end it and start new one
				if (Log::GetCoreLogger()) 
				{
					MU_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);
			if (m_OutputStream.is_open()) {
				m_CurrentSession = new InstrumentationSession{ name };
				WriteHeader();
			}
			else {
				if (Log::GetCoreLogger()) 
				{
					MU_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				//m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};


}

namespace InstrumentorUtils {

	template <size_t N>
	struct ChangeResult
	{
		char Data[N];
	};

	template <size_t N, size_t K>
	constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
	{
		ChangeResult<N> result = {};

		size_t srcIndex = 0;
		size_t dstIndex = 0;
		while (srcIndex < N)
		{
			size_t matchIndex = 0;
			while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
				matchIndex++;
			if (matchIndex == K - 1)
				srcIndex += matchIndex;
			result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
			srcIndex++;
		}
		return result;
	}
}


#define MU_PROFILE 1
#if MU_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define MU_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define MU_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
	#define MU_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define MU_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define MU_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define MU_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define MU_FUNC_SIG __func__
	#else
	#define MU_FUNC_SIG "MU_FUNC_SIG unknown!"
	#endif

	#define MU_PROFILE_BEGIN_SESSION(name, filepath) ::Muto::Instrumentor::Get().BeginSession(name, filepath)
	#define MU_PROFILE_END_SESSION() ::Muto::Instrumentor::Get().EndSession()
	#define MU_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												   ::Muto::InstrumentationTimer timer##line(fixedName##line.Data)
	#define MU_PROFILE_SCOPE_LINE(name, line) MU_PROFILE_SCOPE_LINE2(name, line)
	#define MU_PROFILE_SCOPE(name) MU_PROFILE_SCOPE_LINE(name, __LINE__)
	#define MU_PROFILE_FUNCTION() MU_PROFILE_SCOPE(MU_FUNC_SIG)
#else
	#define MU_PROFILE_BEGIN_SESSION(name, filepath)
	#define MU_PROFILE_END_SESSION()
	#define MU_PROFILE_FUNCTION()
	#define MU_PROFILE_SCOPE(name)
#endif
