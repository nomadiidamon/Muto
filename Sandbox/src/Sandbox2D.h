#pragma once

#include <Vesper.h>

#include "Vesper/App/Layer.h"
#include "Vesper/ParticleSystem/ParticleSystem.h"

struct RandomProperties;

class Sandbox2D : public Vesper::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Vesper::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Vesper::Event& e) override;
private:
	Vesper::OrthographicCameraController m_CameraController;
	glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	glm::vec4 m_ClearColor = { 0.1f, 0.3f, 0.3f, 1.0f };
	int ParticleEmitCount = 100;
	Vesper::ParticleSystem m_ParticleSystem;
	Vesper::ParticleProps m_ParticleProps;
};

