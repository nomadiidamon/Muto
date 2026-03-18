#pragma once
/// @file Vesper.h
/// @author Damon S. Green II
/// @brief Main header file for the Vesper engine.
/// For use by clients in Vesper applications

#include "Vesper/Core/Base.h"

#include "Vesper/App/Application.h"
#include "Vesper/App/Layer.h"

#include "Vesper/Debug/Instrumentor.h"

#include "Vesper/Core/Log.h"
#include "Vesper/Core/Random.h"
#include "Vesper/Core/Color.h"
#include "Vesper/Core/Timestep.h"
#include "Vesper/Core/Timer.h"	
#include "Vesper/Core/Math.h"

#include "Vesper/Input/Input.h"							
/// @todo Input Context class
//#include "Vesper/Input/InputContext.h"				
/// @todo Input Action class
//#include "Vesper/Input/InputAction.h"					
#include "Vesper/Input/KeyCodes.h"
#include "Vesper/Input/MouseButtonCodes.h"

/// GUI
/// @todo Abstract this to OpenGL/DirectX/Vulkan etc ImGui layers
#include "Vesper/ImGui/ImGuiLayer.h"					

#include "Vesper/ParticleSystem/ParticleSystem.h"		

// -- Scene - Entity - Component - System -------------------
#include "Vesper/Scene/Entity.h"
#include "Vesper/Scene/ScriptableEntity.h"
#include "Vesper/Scene/Components.h"

/// @todo Give scene a std::array<System> variable, and add functions to add/remove systems to the scene. Systems will be updated in the scene's OnUpdate function, and will have access to the scene's entity registry. Systems will be responsible for updating the components of the entities in the scene. Systems will be implemented as classes that inherit from a base System class, and will have an OnUpdate function that takes a Timestep as a parameter. Systems will be added to the scene using a template function that takes the system class as a template parameter and forwards any arguments to the system's constructor. Systems will be removed from the scene using a template function that takes the system class as a template parameter.
#include "Vesper/Scene/Scene.h"							

/// @todo Systems class
// #include "Vesper/Scene/Systems.h"					

/// @todo Static SystemsManager class
// #include "Vesper/Scene/SystemsManager.h"				

// -- Renderer-------------------
#include "Vesper/Renderer/Renderer.h"
#include "Vesper/Renderer/Renderer2D.h"
#include "Vesper/Renderer/RenderCommand.h"

#include "Vesper/Renderer/Buffer.h"
#include "Vesper/Renderer/Framebuffer.h"
#include "Vesper/Renderer/Shader.h"
#include "Vesper/Renderer/Texture.h"
#include "Vesper/Renderer/SubTexture2D.h"
#include "Vesper/Renderer/VertexArray.h"

#include "Vesper/Renderer/Camera.h"
#include "Vesper/Renderer/EditorCamera.h"
#include "Vesper/Renderer/OrthographicCamera.h"
#include "Vesper/Renderer/OrthographicCameraController.h"
