#pragma once
/// @file Event.h
/// @author Damon S. Green II
/// @brief Defines the base Event class and related enumerations and macros.

#include "mupch.h"
#include "Core/Base.h"

namespace Muto {
	/// @brief Enumeration of event types.
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/// @brief Enumeration of event categories.
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};


	/// @class Event
	/// @brief Abstract base class for all events.
	class Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		/// @brief Get the type of the event.
		virtual EventType GetEventType() const = 0;
	
		/// @brief Get the name of the event.
		virtual const char* GetName() const = 0;
		
		/// @brief Get the category flags of the event.
		virtual int GetCategoryFlags() const = 0;
		
		/// @brief Convert the event to a string representation.
		virtual std::string ToString() const { return GetName(); }

		/// @brief Check if the event is in a specific category.
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	public:
		/// @brief Indicates whether the event has been handled.
		bool Handled = false;
	};

	/// @class EventDispatcher
	/// @brief Stack-based templated event dispatcher.
	class EventDispatcher
	{
		/// @brief Type alias for event handling functions.
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		/// @brief Construct an EventDispatcher for a specific event.
		///
		/// @param event The event to dispatch.
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		/// @brief Dispatch the event to the appropriate handler if the types match.
		///
		/// @tparam T The type of the event to dispatch.
		/// @param func The function to handle the event.
		/// @return True if the event was handled, false otherwise.
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		/// @brief The event to be dispatched.
		Event& m_Event;
	};

	/// @brief Format an event as a string.
	inline std::string format_as(const Event& e)
	{
		return e.ToString();
	}
}