#include "vzpch.h"
#include "ParticleSystem.h"
#include "Vesper/Renderer/Renderer2D.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

namespace Vesper {

	ParticleSystem::ParticleSystem()
	{
		m_PoolIndex = 999;
		m_ParticlePool.resize(1000);
		m_activeParticleCount = 0;
	}

	ParticleSystem::ParticleSystem(uint32_t maxParticles)
		: m_PoolIndex(maxParticles - 1), m_activeParticleCount(0)
	{
		m_ParticlePool.resize(maxParticles);
	}

	void ParticleSystem::OnUpdate(Vesper::Timestep ts)
	{
		if (m_Loop && m_activeParticleCount == 0)
		{
			ResetSystem();
		}
		else if (!m_Loop && m_activeParticleCount == 0)
		{
			m_IsEmitting = false;
		}
		else if (!m_Loop && m_activeParticleCount > 0)
		{
			m_IsEmitting = false;
		}
		else if (m_Loop) {

			//m_IsEmitting = true;
			if (m_activeParticleCount < m_ParticlePool.size() && m_IsEmitting)
			{
				int particlesToEmit = static_cast<int>(m_EmitRate * m_TimeSinceLastEmit);
				for (int i = 0; i < particlesToEmit; i++)
				{
					Emit(m_Props);
				}
				if (particlesToEmit > 0 && m_EmitRate > 0.0f)
					m_TimeSinceLastEmit -= static_cast<float>(particlesToEmit) / m_EmitRate;
			}
		}



		m_activeParticleCount = 0;
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active) {
				continue;
			}

			particle.LifeRemaining -= ts;
			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;
			m_activeParticleCount++;
		}
		m_TimeSinceLastEmit += ts;
	}

	void ParticleSystem::OnRender()
	{
		for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			float life = particle.LifeRemaining / particle.Lifetime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

			Vesper::Renderer2D::DrawRotatedQuad(
				{ particle.Position },
				{ size, size },
				Vesper::Renderer2D::GetWhiteTexture(),
				particle.Rotation, 1.0f, color);

		}
	}

	void ParticleSystem::Emit(const ParticleProps& particleProps)
	{
		Particle& particle = m_ParticlePool[m_PoolIndex];
		particle.Active = true;
		particle.Position = particleProps.Position + particleProps.PositionVariation * (Vesper::Random::Float3() - glm::vec3(0.5f));
		particle.Rotation = particleProps.Rotation + particleProps.RotationVariation * (Vesper::Random::Float1() - 0.5f);

		particle.Velocity = particleProps.Velocity;
		particle.Velocity.x += particleProps.VelocityVariation.x * (Vesper::Random::Float1() - 0.5f);
		particle.Velocity.y += particleProps.VelocityVariation.y * (Vesper::Random::Float1() - 0.5f);

		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;

		particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Vesper::Random::Float1() - 0.5f);
		particle.SizeEnd = particleProps.SizeEnd;

		particle.Lifetime = particleProps.Lifetime + particleProps.LifetimeVariation * (Vesper::Random::Float1() - 0.5f);
		particle.LifeRemaining = particle.Lifetime;

		uint32_t poolSize = static_cast<uint32_t>(m_ParticlePool.size());
		m_PoolIndex = (m_PoolIndex == 0) ? (poolSize - 1) : (m_PoolIndex - 1);
	}

	void ParticleSystem::ResetParticle(Particle& particle, const ParticleProps& particleProps)
	{
		particle.Active = true;
		particle.Position = particleProps.Position;
		particle.Rotation = particleProps.Rotation + particleProps.RotationVariation * (Vesper::Random::Float1() - 0.5f);
		particle.Velocity = particleProps.Velocity;
		particle.Velocity.x += particleProps.VelocityVariation.x * (Vesper::Random::Float1() - 0.5f);
		particle.Velocity.y += particleProps.VelocityVariation.y * (Vesper::Random::Float1() - 0.5f);
		particle.ColorBegin = particleProps.ColorBegin;
		particle.ColorEnd = particleProps.ColorEnd;
		particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Vesper::Random::Float1() - 0.5f);
		particle.SizeEnd = particleProps.SizeEnd;
		particle.Lifetime = particleProps.Lifetime + particleProps.LifetimeVariation * (Vesper::Random::Float1() - 0.5f);
		particle.LifeRemaining = particle.Lifetime;
	}

}