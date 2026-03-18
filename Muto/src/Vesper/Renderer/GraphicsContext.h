#pragma once
/// @file GraphicsContext.h
/// @author Damon S. Green II
/// @brief Defines the GraphicsContext class, which is responsible for managing the graphics context in the renderer. The GraphicsContext class is an abstract class that defines the interface for graphics contexts. The actual implementation of the graphics context will be done in the RendererAPI-specific classes (e.g., OpenGLGraphicsContext).
/// @note The GraphicsContext class is an abstract class that defines the interface for graphics contexts. The actual implementation of the graphics context will be done in the RendererAPI-specific classes (e.g., OpenGLGraphicsContext).

#include "Vesper/Core/Base.h"

namespace Vesper {

	/// @class GraphicsContext
	/// @brief Abstract class representing a graphics context.
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() {}
		/// @brief Initializes the graphics context.
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	};

}
