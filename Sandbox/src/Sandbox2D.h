#pragma once

#include <Muto.h>

#include "App/Layer.h"
#include "ParticleSystem/ParticleSystem.h"

struct RandomProperties;

class Sandbox2D : public Muto::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Muto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Muto::Event& e) override;
private:
	Muto::OrthographicCameraController m_CameraController;
	glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	glm::vec4 m_ClearColor = { 0.1f, 0.3f, 0.3f, 1.0f };
	int ParticleEmitCount = 100;
	Muto::ParticleSystem m_ParticleSystem;
	Muto::ParticleProps m_ParticleProps;
};

