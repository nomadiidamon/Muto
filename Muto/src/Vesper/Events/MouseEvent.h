#pragma once
/// @file MouseEvent.h
/// @author Damon S. Green II
/// @brief Defines mouse event classes.

#include "vzpch.h"
#include "Vesper/Core/Base.h"
#include "Vesper/Events/Event.h"


namespace Vesper {

	/// @class MouseMovedEvent
	/// @brief Event for registering mouse movement.
	class MouseMovedEvent : public Event
	{
	public:

		/// @brief Construct a MouseMovedEvent with the specified x and y coordinates.
		/// 
		/// @param x The x coordinate of the mouse.
		/// @param y The y coordinate of the mouse.
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		/// @brief Get the x coordinate of the mouse.
		inline float GetX() const { return m_MouseX; }
		/// @brief Get the y coordinate of the mouse.
		inline float GetY() const { return m_MouseY; }

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	/// @class MouseScrolledEvent
	/// @brief Event for registering mouse scroll wheel movement.
	class MouseScrolledEvent : public Event
	{
	public:
		/// @brief Construct a MouseScrolledEvent with the specified x and y offsets.
		///
		/// @param xOffset The offset of the mouse scroll in the x direction.
		/// @param yOffset The offset of the mouse scroll in the y direction.
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		/// @brief Get the x offset of the mouse scroll.
		inline float GetXOffset() const { return m_XOffset; }
		/// @brief Get the y offset of the mouse scroll.
		inline float GetYOffset() const { return m_YOffset; }

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	/// @class MouseButtonEvent
	/// @brief Base class for mouse button events.
	class MouseButtonEvent : public Event
	{
	public:
		/// @brief Get the mouse button associated with the event.
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		/// @brief Construct a MouseButtonEvent with the specified button.
		///
		/// @param button The mouse button associated with the event.
		/// Restricted specific construction to derived classes.
		MouseButtonEvent(int button)
			: m_Button(button) {
		}
		int m_Button;
	};

	/// @class MouseButtonPressedEvent
	/// @brief Event for registering mouse button presses.
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/// @brief Construct a MouseButtonPressedEvent with the specified button.
		///
		/// @param button The mouse button associated with the event.
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {
		}

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << GetMouseButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// @class MouseButtonReleasedEvent
	/// @brief Event for registering mouse button releases.
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		/// @brief Construct a MouseButtonReleasedEvent with the specified button.
		///
		/// @param button The mouse button associated with the event.
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << GetMouseButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}