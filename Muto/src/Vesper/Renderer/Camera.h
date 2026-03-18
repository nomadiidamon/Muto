#pragma once
/// @file Camera.h
/// @author Damon S. Green II
/// @brief Defines the base Camera class that all Camera's derive from. Only contains a projection matrix and a getter.

#include <glm/glm.hpp>


namespace Vesper {

	/// @class Camera
	/// @brief The base Camera class that all Camera's derive from
	/// Only contains a pojection matrix and a getter
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_Projection(projection) {
		}
		~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);

	};

}