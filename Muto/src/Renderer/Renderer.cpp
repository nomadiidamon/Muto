#include "mupch.h"
/// @file Renderer.cpp
/// @author Damon S. Green II
/// @brief Implementation of the Renderer class for the Muto engine.
/// @todo Remove temporary include of OpenGLShader. Should be able to tell the type from our api and cast accordingly, but for now this is fine since we only have one API

#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

namespace Muto {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		MU_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		MU_PROFILE_FUNCTION();
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		MU_PROFILE_FUNCTION();
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		MU_PROFILE_FUNCTION();

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		MU_PROFILE_FUNCTION();
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}