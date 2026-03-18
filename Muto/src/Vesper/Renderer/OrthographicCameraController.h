#pragma once
/// @file OrthographicCameraController.h
/// @author Damon S. Green II
/// @brief Defines the OrthographicCameraController class, which is responsible for controlling an OrthographicCamera. This includes handling input and updating the camera's position and rotation based on that input.
/// @todo Document the OrthographicCameraController class and its methods.

#include "Vesper/Renderer/OrthographicCamera.h"
#include "Vesper/Core/Timestep.h"

#include "Vesper/Events/ApplicationEvent.h"
#include "Vesper/Events/MouseEvent.h"



namespace Vesper {


	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() const { return Right - Left; }
		float GetHeight() const { return Top - Bottom; }

	};


	class OrthographicCameraController
	{
	public: 
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }
		OrthographicCameraBounds GetBounds() const { return m_Bounds; }

		glm::vec3 GetPosition() const { return m_CameraPosition; }
		void SetPosition(float x, float y);

		void SetMoveSpeed(float speed);
		float GetMoveSpeed() const { return m_CameraMoveSpeed; }

		void SetRotation(float rotation);
		float GetRotation() const { return m_CameraRotation; }

		void SetRotationSpeed(float speed);
		float GetRotationSpeed() const { return m_CameraRotationSpeed; }

		float GetAspectRatio() const;
		void SetAspectRatio(float aspectRatio);

		bool CanRotate() const { return m_Rotation; }
		void SetCanRotate(bool canRotate) { m_Rotation = canRotate; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }
		float GetZoomLevel() const { return m_ZoomLevel; }

		void OnImGuiRender();
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		void UpdateCameraBounds();
		void OnUpdateBounds();
		void CalculateView();

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera camera;
		OrthographicCameraBounds m_Bounds;
		
		bool m_Rotation = true;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraMoveSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

	};

}

