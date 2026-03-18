#pragma once
/// @file Math.h
/// @author Damon S. Green II
/// @brief Provides mathematical utility functions.

#include <glm/glm.hpp>


/// @namespace Vesper::Math
/// @brief Contains mathematical utility functions for the Vesper engine.
namespace Vesper::Math {

	/// @brief Decomposes a transformation matrix into its translation, rotation, and scale components.
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

}