#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <random>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Vesper/Core/Log.h"


#include "Vesper/Debug/Instrumentor.h"

/// @file vzpch.h
/// @author Damon S. Green II
/// @brief Precompiled header for the Vesper engine.


#ifdef VZ_PLATFORM_WINDOWS
	#include <windows.h>
#endif

