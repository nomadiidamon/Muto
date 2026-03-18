#pragma once
/// @file LayerStack.h
/// @author Damon S. Green II
/// @brief Defines the LayerStack class for managing a stack of application layers.

#include "Vesper/Core/Base.h"
#include "Layer.h"


namespace Vesper {

	/// @class LayerStack
	/// @brief Manages an ordered stack of Layer pointers. Layers can be pushed or popped and the stack can be iterated in forward or reverse order.
	/// @todo Add layer priority system (maybe?)
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		/// @brief Adds the layer to the stack at the position before the first overlay.
		/// 
		/// @param layer Pointer to the layer to be added.
		void PushLayer(Layer* layer);

		/// @brief Pushes the overlay layer on top of all other layers.
		/// 
		/// @param overlay Pointer to the overlay layer to be added.
		void PushOverlay(Layer* overlay);

		/// @brief Removes the specified layer from the stack.
		/// 
		/// @param layer Pointer to the layer to be removed.
		void PopLayer(Layer* layer);

		/// @brief Removes the specified overlay layer from the stack.
		///
		/// @param overlay Pointer to the overlay layer to be removed.
		void PopOverlay(Layer* overlay);

		/// @brief Returns an iterator to the beginning of the layer stack.
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		/// @brief Returns an iterator to the end of the layer stack.
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		/// @brief Returns a reverse iterator to the beginning of the layer stack.
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		/// @brief Returns a reverse iterator to the end of the layer stack.
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }


	private:
		/// @brief Vector holding pointers to the layers in the stack.
		std::vector<Layer*> m_Layers;
		/// @brief Index indicating where to insert new layers (before overlays).
		unsigned int m_LayerInsertIndex = 0;
	};


}
