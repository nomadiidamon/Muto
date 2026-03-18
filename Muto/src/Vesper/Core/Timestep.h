#pragma once
/// @file Timestep.h
/// @author Damon S. Green II
/// @brief Declares the Timestep class representing a time step in seconds.

namespace Vesper {

	/// @class Timestep
	/// @brief Represents a time step in seconds.
	class Timestep
	{
	public:
		/// @brief Constructs a Timestep with the given time in seconds.
		///
		/// @param time The time in seconds.

		Timestep(float time = 0.0f)
			: m_Time(time) 
		{
		}

		operator float() const { return m_Time; }

		/// @brief Returns the time in seconds.
		float GetSeconds() const { return m_Time; }
		/// @brief Returns the time in milliseconds.
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}