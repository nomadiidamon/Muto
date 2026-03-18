#include <Vesper/ImGui/VesperImGui.h>

#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	VZ_PROFILE_FUNCTION();
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
	VZ_PROFILE_FUNCTION();

	m_ParticleProps.Position = { 0.0f, 0.0f, 0.0f };
	m_ParticleProps.Velocity = { 0.0f, 0.0f, 0.0f };
	m_ParticleProps.VelocityVariation = { 1.0f, 1.0f, 0.0f };
	m_ParticleProps.ColorBegin = { 1.0f, 0.5f, 0.2f, 1.0f };
	m_ParticleProps.ColorEnd = { 0.2f, 0.3f, 0.8f, 1.0f };
	m_ParticleProps.SizeBegin = 0.5f;
	m_ParticleProps.SizeEnd = 0.0f;
	m_ParticleProps.Lifetime = 3.0f;
	m_ParticleProps.Rotation = 0.0f;
	m_ParticleProps.RotationVariation = 27.0f;

	m_ParticleSystem = Vesper::ParticleSystem(35000);
	m_ParticleSystem.SetParticleProps(m_ParticleProps);
	Vesper::RenderCommand::SetClearColor(m_ClearColor);
	Vesper::RenderCommand::Clear();
	m_CameraController.SetZoomLevel(3.5f);
}

void Sandbox2D::OnDetach()
{
	VZ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Vesper::Timestep ts)
{
	VZ_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Vesper::Renderer2D::ResetStats();
	{
		VZ_PROFILE_SCOPE("Renderer Prep");
		Vesper::RenderCommand::Clear();
	}

	{
			VZ_PROFILE_SCOPE("Particle Scene");
			Vesper::Renderer2D::BeginScene(m_CameraController.GetCamera());

			if (Vesper::Input::IsMouseButtonPressed(Vesper::Mouse::ButtonLeft))
			{
				if (m_ParticleSystem.m_TimeSinceLastEmit >= 0.016f) {

					glm::vec2 mousePos = Vesper::Input::GetMousePosition();
					auto width = Vesper::Application::Get().GetWindow().GetWidth();
					auto height = Vesper::Application::Get().GetWindow().GetHeight();

					auto bounds = m_CameraController.GetBounds();
					m_ParticleProps.Position.x = (mousePos.x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f + m_CameraController.GetPosition().x;
					m_ParticleProps.Position.y = bounds.GetHeight() * 0.5f - (mousePos.y / height) * bounds.GetHeight() + m_CameraController.GetPosition().y;
					m_ParticleSystem.m_IsEmitting = true;
					for (int i = 0; i < ParticleEmitCount; i++) {
						m_ParticleSystem.Emit(m_ParticleProps);
					}
					m_ParticleSystem.m_TimeSinceLastEmit = 0.0f;
				}
			}
			else {
				m_ParticleSystem.m_IsEmitting = false;
			}

			m_ParticleSystem.OnUpdate(ts);
			m_ParticleSystem.OnRender();
			Vesper::Renderer2D::EndScene();	
	}
}

void Sandbox2D::OnImGuiRender()
{
	VZ_PROFILE_FUNCTION();

	{
		ImGui::Begin("Settings");
		ImGui::Text("Renderer2D Stats:");
		auto stats = Vesper::Renderer2D::GetStats();
		ImGui::Text("\tDraw Calls: %d", stats.DrawCalls);
		ImGui::Text("\tQuad Count: %d", stats.QuadCount);
		ImGui::Text("\tVertex Count: %d", stats.GetTotalVertexCount());
		ImGui::Text("\tIndex Count: %d", stats.GetTotalIndexCount());
		ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Separator();

		ImGui::Text("Particle System Settings:");
		ImGui::DragInt("Particle Emit Count", &ParticleEmitCount, 1, 0, 1000);
		ImGui::DragFloat("Particle Lifetime", &m_ParticleProps.Lifetime, 0.1f, 0.0f, 15.0f);
		ImGui::DragFloat("Particle Lifetime Variation", &m_ParticleProps.LifetimeVariation, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat3("Particle Velocity Variation", glm::value_ptr(m_ParticleProps.VelocityVariation), 0.05f, -10.0f, 10.0f);
		ImGui::SliderFloat("Particle Size", &m_ParticleProps.SizeBegin, 0.05f, 5.0f);
		ImGui::ColorEdit4("Particle Color Begin", glm::value_ptr(m_ParticleProps.ColorBegin));
		ImGui::ColorEdit4("Particle Color End", glm::value_ptr(m_ParticleProps.ColorEnd));

		if (ImGui::ColorEdit4("Background Color", glm::value_ptr(m_ClearColor)))
		{
			Vesper::RenderCommand::SetClearColor(m_ClearColor);
		}
		if (ImGui::Button("Clear Screen"))
		{
			Vesper::RenderCommand::Clear();
			Vesper::RenderCommand::SetClearColor(m_ClearColor);
		}
		ImGui::End();
	}

	Vesper::DisplayVesperInfo_ImGui();

}


void Sandbox2D::OnEvent(Vesper::Event& e)
{
	m_CameraController.OnEvent(e);
}
