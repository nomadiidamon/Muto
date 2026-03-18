#pragma once
/// @file KeyEvent.h
/// @author Damon S. Green II
/// @brief Defines keyboard event classes.

#include "vzpch.h"
#include "Vesper/Core/Base.h"
#include "Vesper/Events/Event.h"


namespace Vesper {

	/// @class KeyEvent
	/// @brief Base class for keyboard events.
	class KeyEvent : public Event
	{
	public:

		/// @brief Get the key code associated with the event.
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:

		/// @brief Construct a KeyEvent with the specified key code.
		///
		/// @param keycode The key code associated with the event.
		/// Restricted specific construction to derived classes.
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	/// @class KeyPressedEvent
	/// @brief Event for registering key press.
	class KeyPressedEvent : public KeyEvent
	{
	public:

		/// @brief Construct a KeyPressedEvent with the specified key code and repeat count.
		///
		/// @param keycode The key code associated with the event.
		/// @param repeatCount The number of times the key press is repeated.
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		/// @brief Get the repeat count of the key press event.
		inline int GetRepeatCount() const { return m_RepeatCount; }

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	/// @class KeyReleasedEvent
	/// @brief Event for registering key release.
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		/// @brief Construct a KeyReleasedEvent with the specified key code.
		/// 
		/// @param keycode The key code associated with the event.
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/// @class KeyTypedEvent
	/// @brief Event for registering key typing.
	class KeyTypedEvent : public KeyEvent
	{
	public:
		/// @brief Construct a KeyTypedEvent with the specified key code.
		///
		/// @param keycode The key code associated with the event.
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {
		}

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}