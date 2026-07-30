#pragma once
/// @file EditorCamera.h
/// @author Damon S. Green II
/// @brief Defines the EditorCamera class, which is responsible for displaying data when using the editor. Derives from the Camera class.

#include "Camera.h"
#include "Core/Timestep.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include <glm/glm.hpp>


namespace Muto {

	/// @class Editor Camera
	/// @brief The camera class responsible for displaying data when using the editor
	/// @note Derives from the Camera class
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();
		EditorCamera(float fov, float aspectRation, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width, m_ViewportHeight = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjection() const { return m_Projection * m_ViewMatrix; }
		
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::quat GetOrientation() const;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		float GetPitch() const { return m_Pitch; }
		void SetPitch(float pitch) { m_Pitch = pitch; }

		float GetYaw() const { return m_Yaw; }
		void SetYaw(float yaw) { m_Yaw = yaw; }
	private:
		void UpdateProjection();
		void UpdateView();
		
		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;


	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = glm::vec3(1.0f);

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;

	};
}
