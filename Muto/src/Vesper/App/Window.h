#pragma once
/// @file Window.h
/// @author Damon S. Green II
/// @brief Defines the abstract Window class and WindowProps struct for window management.
/// @todo Add support for different window modes (windowed, fullscreen, borderless).
#include "vzpch.h"

#include "Vesper/Core/Base.h"
#include "Vesper/Events/Event.h"

namespace Vesper {

	/// WIP
	enum class WindowMode
	{
		Windowed = 0,
		Fullscreen = 1,
		Borderless = 2
	};

	/// @brief Holds the data for window configuration
	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		/// @brief Constructor to initialize WindowProps with given or default values.
		///
		/// @param title The title of the window.
		/// @param width The width of the window.
		/// @param height The height of the window.
		WindowProps(const std::string& title = "Vesper Engine",
			uint32_t width = 1600,
			uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	/// @class Window
	/// @brief Abstract interface representing an application window.
	/// @todo Add Window mode functionality
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		
		/// @brief Called every frame to update the window.
		virtual void OnUpdate() = 0;

		/// @brief Retrieves the width of the window.
		virtual uint32_t GetWidth() const = 0;
		/// @brief Retrieves the height of the window.
		virtual uint32_t GetHeight() const = 0;

		/// @brief Sets the callback function for window events.
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		/// @brief Sets whether vertical synchronization (VSync) is enabled.
		virtual void SetVSync(bool enabled) = 0;
		/// @brief Checks if vertical synchronization (VSync) is enabled.
		virtual bool IsVSync() const = 0;
		
		/// @brief Retrieves the native window handle.
		virtual void* GetNativeWindow() const = 0;

		/// @brief Creates a window instance with the specified properties.
		///
		/// @param props The properties to initialize the window with.
		/// @return A scoped pointer to the created window instance.
		static Scope<Window> Create(const WindowProps& props = WindowProps());

	};
}