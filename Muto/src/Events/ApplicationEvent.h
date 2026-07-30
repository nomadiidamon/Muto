#pragma once
/// @file ApplicationEvent.h
/// @author Damon S. Green II
/// @brief Defines application event classes.

#include "mupch.h"
#include "Core/Base.h"
#include "Events/Event.h"


namespace Muto {

	/// @class WindowResizeEvent
	/// @brief Event for registering window resize.
	class WindowResizeEvent : public Event
	{
	public:

		/// @brief Construct a WindowResizeEvent with the specified width and height.
		///
		/// @param width The new width of the window.
		/// @param height The new height of the window.
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		/// @brief Get the new width of the window.
		unsigned int GetWidth() const { return m_Width; }
		/// @brief Get the new height of the window.
		unsigned int GetHeight() const { return m_Height; }

		/// @brief Convert the event to a string representation.
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	/// @class WindowCloseEvent
	/// @brief Event for registering window close.
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @class AppTickEvent
	/// @brief Event for registering application tick.
	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @class AppUpdateEvent
	/// @brief Event for registering application update.
	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// @class AppRenderEvent
	/// @brief Event for registering application render.
	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}