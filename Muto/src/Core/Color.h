#pragma once
/// @file Color.h
/// @author Damon S. Green II
/// @brief Provides commonly used colors and color manipulation functions.

#include <glm/glm.hpp>


namespace Muto {

	/// @namespace Muto::Color
	/// @brief Provides commonly used colors and color manipulation functions.
	namespace Color {

		/// @brief Returns a vec4 representing the color white.
		static glm::vec4 White() { return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color black.
		static glm::vec4 Black() { return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color gray.
		static glm::vec4 Gray() { return glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); }

		/// @brief Returns a vec4 representing the color red.
		static glm::vec4 Red() { return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color orange.
		static glm::vec4 Orange() { return glm::vec4(1.0f, 0.5f, 0.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color yellow.
		static glm::vec4 Yellow() { return glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color green.
		static glm::vec4 Green() { return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color blue.
		static glm::vec4 Blue() { return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color indigo.
		static glm::vec4 Indigo() { return glm::vec4(0.29f, 0.0f, 0.51f, 1.0f); }
		/// @brief Returns a vec4 representing the color purple.
		static glm::vec4 Purple() { return glm::vec4(0.5f, 0.0f, 0.5f, 1.0f); }

		/// @brief Returns a vec4 representing the color cyan.
		static glm::vec4 Cyan() { return glm::vec4(0.0f, 1.0f, 1.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color magenta.
		static glm::vec4 Magenta() { return glm::vec4(1.0f, 0.0f, 1.0f, 1.0f); }
		/// @brief Returns a vec4 representing the color pink.
		static glm::vec4 Pink() { return glm::vec4(1.0f, 0.75f, 0.8f, 1.0f); }
		/// @brief Returns a vec4 representing the color brown.
		static glm::vec4 Brown() { return glm::vec4(0.6f, 0.4f, 0.2f, 1.0f); }
		/// @brief Returns a vec4 representing a fully transparent color.
		static glm::vec4 Transparent() { return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); }

		/// @brief Strips the alpha component from the given color, setting it to 1.0 (fully opaque).
		static glm::vec4 StripAlpha(const glm::vec4& color) {	return glm::vec4(color.x, color.y, color.z, 1.0f);	}
		/// @brief Sets the alpha component of the given color to the specified value.
		static glm::vec4 SetAlpha(const glm::vec4& color, float alpha = 0.0f) {	return glm::vec4(color.x, color.y, color.z, alpha);}
	}

}