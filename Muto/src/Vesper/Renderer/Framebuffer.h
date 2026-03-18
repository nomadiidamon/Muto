#pragma once
/// @file Framebuffer.h
/// @author Damon S. Green II
/// @brief Defines the Framebuffer class, which is responsible for managing framebuffer objects in the renderer.
/// @note The Framebuffer class is an abstract class that defines the interface for framebuffer objects. The actual implementation of the framebuffer will be done in the RendererAPI-specific classes (e.g., OpenGLFramebuffer).

#include "Vesper/Core/Base.h"

namespace Vesper {


	/// @brief Specification for creating a Framebuffer.
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		// FramebufferFormat Format = FramebufferFormat::RGBA8;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	
	/// @class Framebuffer
	/// @brief Abstract class representing a framebuffer.
	class Framebuffer
	{
	public:
		~Framebuffer() = default;


		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		/// @brief Resizes the framebuffer to the given width and height.
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		/// @brief Returns the renderer ID of the color attachment texture.
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		/// @brief Returns the specification used to create the framebuffer.
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		
		/// @brief Creates a framebuffer with the given specification.
		///
		/// @param spec The specification for the framebuffer.
		/// @return A reference-counted pointer to the created framebuffer.
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};

}
