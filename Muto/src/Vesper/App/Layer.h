#pragma once
/// @file Layer.h
/// @author Damon S. Green II
/// @brief Defines the Layer class for creating reusable application layers.
/// @todo Add layer priority system (maybe?)

#include "Vesper/Core/Timestep.h"
#include "Vesper/Events/Event.h"


namespace Vesper {

	/// @class Layer
	/// @brief Represents a reusable application layer that receives lifecycle callbacks (attach, detach, update, events, render, and ImGui render). 
	/// Intended as a base class for concrete layers.
	class Layer
	{
	public:

		/// @brief Constructs a Layer with an optional name for debugging purposes.
		///
		/// @param name The name of the layer, used for debugging, defaulted to "Layer".
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		/// @brief Called when the layer is attached to the application.
		virtual void OnAttach() {};

		/// @brief Called when the layer is detached from the application.
		virtual void OnDetach() {};

		/// @brief Called every frame to update the layer with the given timestep.
		///
		/// @param ts The timestep representing the time elapsed since the last update.
		virtual void OnUpdate(Timestep ts) {};

		/// @brief Called when an event is dispatched to the layer.
		///
		/// @param event The event being dispatched.
		virtual void OnEvent(Event& event){}

		/// @brief Called when the layer should render its contents.
		///
		/// @note Layers are responsible for their own rendering needs.
		/// @todo add layer rendering into the application's render loop
		virtual void OnRender() {};

		/// @brief Called when the layer should render its ImGui components.
		virtual void OnImGuiRender() {};

		/// @brief Retrieves the name of the layer for debugging purposes.
		inline const std::string& GetName() const { return m_DebugName; }
	protected:

		/// @brief The name of the layer assigned at creation, used for debugging.
		std::string m_DebugName;
	};

}