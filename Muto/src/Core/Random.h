#pragma once
/// @file Random.h
/// @author Damon S. Green II
/// @brief Provides random number generation utilities.

#include <random>
#include <algorithm>
#include <cstdint>
#include <glm/glm.hpp>
#include "Debug/Instrumentor.h"


namespace Muto {

	/// @namespace Random
	/// @brief Provides various functions and helpers related to randomization
	namespace Random {

		inline std::mt19937& GetRNG() {
			static thread_local std::mt19937 rng{ std::random_device{}() };
			return rng;
		}

		inline void Seed(uint32_t seed) {
			GetRNG().seed(seed);
		}
		
		inline uint32_t UInt1(uint32_t max) {
			MU_PROFILE_FUNCTION();
			std::uniform_int_distribution<uint32_t> dist(0, max - 1);
			return dist(GetRNG());
		}

		inline bool Bool1(float trueChance) {
			MU_PROFILE_FUNCTION();
			std::uniform_real_distribution<float> dist(0.0f, 1.0f);
			return dist(GetRNG()) < trueChance;
		}

		inline unsigned char Char() {
			MU_PROFILE_FUNCTION();
			std::uniform_int_distribution<int> dist(0, 255);
			return static_cast<unsigned char>(dist(GetRNG()));
		}

		inline std::string String(size_t length) {
			MU_PROFILE_FUNCTION();
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			std::string str(length, 0);
			for (size_t i = 0; i < length; ++i) {
				str[i] = charset[UInt1(static_cast<uint32_t>(max_index))];
			}
			return str;
		}

		inline std::string HexString(size_t length) {
			MU_PROFILE_FUNCTION();
			const char charset[] =
				"0123456789"
				"ABCDEF";
			const size_t max_index = (sizeof(charset) - 1);
			std::string str(length, 0);
			for (size_t i = 0; i < length; ++i) {
				str[i] = charset[UInt1(static_cast<uint32_t>(max_index))];
			}
			return str;
		}

		inline std::string UUID() {
			MU_PROFILE_FUNCTION();
			return HexString(8) + "-" + HexString(4) + "-" + HexString(4) + "-" + HexString(4) + "-" + HexString(12);
		}

		// Returns a float in the range [0.0, 1.0] = [inclusive, exclusive]
		inline float Float1() {
			MU_PROFILE_FUNCTION();
			static thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);
			return dist(GetRNG());
		}

		// Returns a float in the range [min, max]
		// If you need max to be possible, use the "_Inclusive" variant which advances the upper bound
		inline float RangeF1(float min, float max) {
			MU_PROFILE_FUNCTION();
			if (min > max) std::swap(min, max);
			std::uniform_real_distribution<float> dist(min, max);
			return dist(GetRNG());
		}

		// Inclusive-upper variant: returns value in [min, max] (max possible)
		inline float RangeF1_Inclusive(float min, float max) {
			if (min > max) std::swap(min, max);
			float upper = std::nextafter(max, std::numeric_limits<float>::infinity());
			std::uniform_real_distribution<float> dist(min, upper);
			return dist(GetRNG());
		}

		// Returns a 2D float vector with each component in the range [0.0, 1.0] = [inclusive, exclusive]
		inline glm::vec2 Float2() {
			return glm::vec2{ Float1(), Float1() };
		}

		// Returns a 2D float vector with each component in the range [min, max]
		inline glm::vec2 RangeF2(float min, float max) {
			return glm::vec2{ RangeF1(min, max), RangeF1(min, max) };
		}

		// Returns a 2D float vector with each component in the range defined by the components of the given vector
		inline glm::vec2 RangeF2(float min1, float max1, float min2, float max2) {
			return glm::vec2{ RangeF1(min1, max1), RangeF1(min2, max2) };
		}

		// Returns a 2D float vector with each component in the specified ranges
		inline glm::vec2 RangeF2(const glm::vec2& minRange, const glm::vec2& maxRange) {
			return glm::vec2{ RangeF1(minRange.x, maxRange.x), RangeF1(minRange.y, maxRange.y) };
		}


		// Returns a 3D float vector with each component in the range [0.0, 1.0] = [inclusive, exclusive]
		inline glm::vec3 Float3() {
			return glm::vec3{ Float1(), Float1(), Float1() };
		}

		// Returns a 3D float vector with each component in the range [min, max]
		inline glm::vec3 RangeF3(float min, float max) {
			return glm::vec3{ RangeF1(min, max), RangeF1(min, max), RangeF1(min, max) };
		}

		// Returns a 3D float vector with each component in the specified ranges
		inline glm::vec3 RangeF3(float min1, float max1, float min2, float max2, float min3, float max3) {
			return glm::vec3{ RangeF1(min1, max1), RangeF1(min2, max2), RangeF1(min3, max3) };
		}

		// Returns a 3D float vector with each component in the specified ranges
		inline glm::vec3 RangeF3(const glm::vec2& range1, const glm::vec2& range2, const glm::vec2& range3) {
			return glm::vec3{ RangeF1(range1.x, range1.y), RangeF1(range2.x, range2.y), RangeF1(range3.x, range3.y) };
		}

		// Returns a 4D float vector with each component in the range [0.0, 1.0] = [inclusive, exclusive]
		inline glm::vec4 Float4() {
			return glm::vec4{ Float1(), Float1(), Float1(), Float1() };
		}

		// Returns a 4D float vector with each component in the range [min, max]
		inline glm::vec4 RangeF4(float min, float max) {
			return glm::vec4{ RangeF1(min, max), RangeF1(min, max), RangeF1(min, max), RangeF1(min, max) };
		}




	}
}