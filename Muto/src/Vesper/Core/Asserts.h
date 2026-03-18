#pragma once
/// @file Asserts.h
/// @author Damon S. Green II
/// @brief Provides assertion macros for debugging and error handling.


/// ASSERT MACROS
#ifdef VZ_DEBUG
#define VZ_ENABLE_ASSERTS
#endif	

#ifdef VZ_ENABLE_ASSERTS
/// @brief Asserts that the given condition is true. If not, logs an error message and triggers a breakpoint.
#define VZ_ASSERT(x, ...) { if(!(x)) { VZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
/// @brief Asserts that the given condition is true in core code. If not, logs an error message and triggers a breakpoint.
#define VZ_CORE_ASSERT(x, ...) { if(!(x)) { VZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define VZ_ASSERT(x, ...)
#define VZ_CORE_ASSERT(x, ...)
#endif