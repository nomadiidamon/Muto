#pragma once
/// @file Asserts.h
/// @author Damon S. Green II
/// @brief Provides assertion macros for debugging and error handling.


/// ASSERT MACROS
#ifdef MU_DEBUG
#define MU_ENABLE_ASSERTS
#endif	

#ifdef MU_ENABLE_ASSERTS
/// @brief Asserts that the given condition is true. If not, logs an error message and triggers a breakpoint.
#define MU_ASSERT(x, ...) { if(!(x)) { MU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
/// @brief Asserts that the given condition is true in core code. If not, logs an error message and triggers a breakpoint.
#define MU_CORE_ASSERT(x, ...) { if(!(x)) { MU_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define MU_ASSERT(x, ...)
#define MU_CORE_ASSERT(x, ...)
#endif