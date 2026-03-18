#pragma once
/// @file ParticleSystem.h
/// @author Damon S. Green II
/// @brief Defines the ParticleSystem class, which is responsible for rendering a simple particle system. This is a temporary implementation and will be replaced with a more robust implementation in the future.

#include <glm/glm.hpp>
#include "Vesper/Core/Timestep.h"

namespace Vesper {

	struct ParticleProps
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 PositionVariation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Velocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 VelocityVariation = { 0.0f, 0.0f, 0.0f };
		glm::vec4 ColorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 ColorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
		float SizeBegin = 1.0f;
		float SizeEnd = 0.0f;
		float SizeVariation = 0.0f;
		float Rotation = 0.0f;
		float RotationVariation = 0.0f;
		float Lifetime = 1.0f;
		float LifetimeVariation = 0.0f;
	};

	struct Particle
	{
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd;
		float Rotation;
		float Lifetime = 0.0f;
		float LifeRemaining = 0.0f;
		bool Active = false;
	};

	/// @class ParticleSystem
	/// @brief A simple particle system for stress testing the renderer. This is a temporary starter particle system and will be replaced with a more robust implementation in the future.
	/// @note Temporary implementation is not optimized for performance and is intended for testing purposes only. 
	/// It uses a simple pool of particles and updates them each frame. The particle properties can be set using the ParticleProps struct, which allows for variation in velocity, size, rotation, and lifetime.
	class ParticleSystem
	{
	public:
		ParticleSystem();
		ParticleSystem(uint32_t maxParticles);

		void OnUpdate(Timestep ts);
		void OnRender();
		void Emit(const ParticleProps& particleProps);
		void SetParticleProps(const ParticleProps& particleProps) { m_Props = particleProps; }
		void ResetSystem() { m_PoolIndex = m_ParticlePool.size() - 1; m_TimeSinceLastEmit = 0.0f; m_IsEmitting = true; }
		void ResetParticle(Particle& particle, const ParticleProps& particleProps);
	private:
		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 999;
		int m_activeParticleCount = 0;
	public:
		ParticleProps m_Props;
		float m_TimeSinceLastEmit = 0.0f;
		bool m_IsEmitting = true;
		int m_EmitRate = 100; // Particles per second
		bool m_Loop = true;
	};


}