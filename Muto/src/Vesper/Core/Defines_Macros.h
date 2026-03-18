#pragma once
/// @file Defines_Macros.h
/// @author Damon S. Green II
/// @brief Provides commonly used macros along with project wide typedefs.


/// @brief Macro to shift 1 by x positions to create a bitmask.
/// @param x The number of positions to shift.
/// @return The resulting bitmask.
/// @note This macro is typically used for defining event categories.
/// @warning Be cautious when using this macro with values greater than or equal to the number of bits in an integer, as it may lead to undefined behavior.
/// @attention This macro is not type-safe; consider using constexpr functions or enum classes for better type safety.
#define BIT(x) (1 << x)

/// @brief Binds a member function as an event handler.
/// @param fn The member function to bind.
#define VZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

/// @brief Binds the given member function of the Application class as an event handler.
/// @param x The member function to bind.
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

/// @brief Macro to define event type in event subclasses.
/// @param type The event type to define.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

/// @brief Macro to define event category in event subclasses.
/// @param category The event category to define.
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


/// @namespace Vesper
/// @brief The main namespace for the Vesper engine.
namespace Vesper
{
	/// @brief A smart pointer type representing exclusive ownership of an object.
	///
	/// @tparam T The type of object to manage.
	/// @note This is an alias for std::unique_ptr.
	template <typename T>
	using Scope = std::unique_ptr<T>;

	/// @brief Creates a Scope (unique_ptr) for the given type and constructor arguments.
	///
	/// @tparam T The type of object to create.
	/// @tparam Args The types of constructor arguments.
	/// @param args The constructor arguments.
	/// @return A Scope (unique_ptr) managing the created object.
	template <typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	/// @brief A smart pointer type representing shared ownership of an object.
	///
	/// @tparam T The type of object to manage.
	/// @note This is an alias for std::shared_ptr.
	template <typename T>
	using Ref = std::shared_ptr<T>;

	/// @brief Creates a Ref (shared_ptr) for the given type and constructor arguments.
	///
	/// @tparam T The type of object to create.
	/// @tparam Args The types of constructor arguments.
	/// @param args The constructor arguments.
	/// @return A Ref (shared_ptr) managing the created object.
	template <typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}