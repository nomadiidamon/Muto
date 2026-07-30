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

#include "Core/Log.h"


#include "Debug/Instrumentor.h"

/// @file mupch.h
/// @author Damon S. Green II
/// @brief Precompiled header for the Muto engine.


#ifdef MU_PLATFORM_WINDOWS
	#include <windows.h>
#endif

