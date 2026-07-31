#include "Sandbox2D.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Gateware/Gateware.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	MU_PROFILE_FUNCTION();
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
	MU_PROFILE_FUNCTION();

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

	m_ParticleSystem = Muto::ParticleSystem(35000);
	m_ParticleSystem.SetParticleProps(m_ParticleProps);
	Muto::RenderCommand::SetClearColor(m_ClearColor);
	Muto::RenderCommand::Clear();
	m_CameraController.SetZoomLevel(3.5f);
}

void Sandbox2D::OnDetach()
{
	MU_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Muto::Timestep ts)
{
	MU_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Muto::Renderer2D::ResetStats();
	{
		MU_PROFILE_SCOPE("Renderer Prep");
		Muto::RenderCommand::Clear();
	}

	{
			MU_PROFILE_SCOPE("Particle Scene");
			Muto::Renderer2D::BeginScene(m_CameraController.GetCamera());

			if (Muto::Input::IsMouseButtonPressed(Muto::Mouse::ButtonLeft))
			{
				if (m_ParticleSystem.m_TimeSinceLastEmit >= 0.016f) {

					glm::vec2 mousePos = Muto::Input::GetMousePosition();
					auto width = Muto::Application::Get().GetWindow().GetWidth();
					auto height = Muto::Application::Get().GetWindow().GetHeight();

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
			Muto::Renderer2D::EndScene();	
	}
}

void Sandbox2D::OnImGuiRender()
{
	MU_PROFILE_FUNCTION();

	{
		ImGui::Begin("Settings");
		ImGui::Text("Renderer2D Stats:");
		auto stats = Muto::Renderer2D::GetStats();
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
			Muto::RenderCommand::SetClearColor(m_ClearColor);
		}
		if (ImGui::Button("Clear Screen"))
		{
			Muto::RenderCommand::Clear();
			Muto::RenderCommand::SetClearColor(m_ClearColor);
		}
		ImGui::End();
	}

}


void Sandbox2D::OnEvent(Muto::Event& e)
{
	m_CameraController.OnEvent(e);
}
