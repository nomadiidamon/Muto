#pragma once
/// @file UniformBuffer.h
/// @author Damon S. Green II
/// @brief Defines the UniformBuffer class, which is an abstraction for a uniform buffer object (UBO).
/// @note The UniformBuffer class provides an interface for setting data in a uniform buffer, and includes a static Create method for instantiating uniform buffers.

#include "Core/Base.h"

namespace Muto {

	/// @class UniformBuffer
	/// @brief An abstraction for a uniform buffer object (UBO).
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};

}