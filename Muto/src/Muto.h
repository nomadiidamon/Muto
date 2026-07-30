#pragma once
/// @file Muto.h
/// @author Damon S. Green II
/// @brief Main header file for the Muto engine.
/// For use by clients in Vesper applications

#include "Core/Base.h"

#include "App/Application.h"
#include "App/Layer.h"

#include "Debug/Instrumentor.h"

#include "Core/Log.h"
#include "Core/Random.h"
#include "Core/Color.h"
#include "Core/Timestep.h"
#include "Core/Timer.h"	
#include "Core/Math.h"

#include "Input/Input.h"							
/// @todo Input Context class
//#include "Input/InputContext.h"				
/// @todo Input Action class
//#include "Input/InputAction.h"					
#include "Input/KeyCodes.h"
#include "Input/MouseButtonCodes.h"

/// GUI
/// @todo Abstract this to OpenGL/DirectX/Vulkan etc ImGui layers
#include "GUI/ImGui/ImGuiLayer.h"

#include "ParticleSystem/ParticleSystem.h"		

// -- Scene - Entity - Component - System -------------------
#include "Scene/Entity.h"
#include "Scene/ScriptableEntity.h"
#include "Scene/Components.h"

/// @todo Give scene a std::array<System> variable, and add functions to add/remove systems to the scene. Systems will be updated in the scene's OnUpdate function, and will have access to the scene's entity registry. Systems will be responsible for updating the components of the entities in the scene. Systems will be implemented as classes that inherit from a base System class, and will have an OnUpdate function that takes a Timestep as a parameter. Systems will be added to the scene using a template function that takes the system class as a template parameter and forwards any arguments to the system's constructor. Systems will be removed from the scene using a template function that takes the system class as a template parameter.
#include "Scene/Scene.h"							

/// @todo Systems class
// #include "Scene/Systems.h"					

/// @todo Static SystemsManager class
// #include "Scene/SystemsManager.h"				

// -- Renderer-------------------
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffer.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Camera.h"
#include "Renderer/EditorCamera.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/OrthographicCameraController.h"
