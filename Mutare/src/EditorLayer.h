#pragma once

#include <Vesper.h>

#include "Vesper/App/Layer.h"
#include "Vesper/ParticleSystem/ParticleSystem.h"
#include "Vesper/Scene/Scene.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Vesper/Renderer/EditorCamera.h"

namespace Vesper {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		void ResetScene();
	private:
		SceneHierarchyPanel m_SceneHierarchyPanel;
		
		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;

		enum class SceneState
		{
			Edit = 0, Play = 1, Simulate = 2
		};
		SceneState m_SceneState = SceneState::Edit;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {0,0};
		glm::vec2 m_ViewportBounds[2] = { {0,0}, {0,0} };
		bool m_PrimaryCamera = true;
		Entity m_CameraEntity;
		//Entity m_SecondaryCameraEntity;
		int m_GizmoType = -1;
		float m_TranslationSnap = 0.5f, m_RotationSnap = 45.0f, m_ScaleSnap = 0.5f;
		
		OrthographicCameraController m_CameraController;

		float lastFrameTime = 0.0f;
		Entity m_FireEntity, m_SmokeEntity;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Texture2D> m_SpriteSheetFire;
		Ref<Texture2D> m_SpriteSheetSmoke;
		Ref<Texture2D> m_SpriteSheetTown;
		Ref<Texture2D> m_SpriteSheetCrystals;
		Ref<Texture2D> m_SpriteSheetRocks;
		Ref<Texture2D> m_SpriteSheetCursedLands;

		Ref<SubTexture2D> m_SubTextureFire;
		Ref<SubTexture2D> m_SubTextureSmoke;
		Ref<SubTexture2D> m_SubTextureTown;
		//Ref<SubTexture2D> m_SubTextureCrystal;
		//Ref<SubTexture2D> m_SubTextureRock;
		//Ref<SubTexture2D> m_SubTexturePlant;

		Ref<Framebuffer> m_Framebuffer;

		EditorCamera m_EditorCamera;

		float m_textureScale = 1.0f;
		float m_squareRotation = 25.0f;
		float m_specialQuadRotation = 0.5f;
		int m_ParticleEmitCount = 100;

		ParticleSystem m_ParticleSystem;	
		ParticleProps m_ParticleProps;


		bool scene1 = false, scene2 = false, scene3 = false, scene4 = false;
		bool useEntityScene = true;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 m_TextureTintColor1 = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 m_TextureTintColor2 = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		glm::vec4 m_ClearColor = { 0.1f, 0.3f, 0.3f, 1.0f };
		glm::vec4 m_SpecialQuadColor = { 0.9f, 0.2f, 0.8f, 1.0f };
		bool m_UseSpecialQuadColor = false;

		std::unordered_map<char, Ref<SubTexture2D>>s_TextureMap;

	};


}