# Muto

Muto is a lightweight graphics application inspired by TheCherno's Game Engine Architecture series for the Hazel engine.  
It provides a renderer, scene & entity system, editor UI, input handling, and utilities to build simple games and interactive applications in C++ (C++17).

## Quick overview

- Third-party libraries:
  - entt (entity-component system)
  - Glad (OpenGL function loading)
  - GLFW (windowing and input)
  - glm (math library)
  - ImGui (editor UI)
  - ImGuizmo (editor gizmos)
  - spdlog (logging)
  - stb (image loading)
- Core features:
  - Scene / Entity / Component system
  - 2D renderer with orthographic and perspective cameras
  - ImGui-based editor layer
  - Input and event handling
  - Starter particle system and instrumentation

## New Project example code

The easiest way to get started with Muto is to simply modify the Sandbox project. The following is an example of a simple application that creates a layer and renders a simple ImGui window.

```cpp
#include <Muto.h>
#include <App/EntryPoint.h> // can only be included in one source file

#include "imgui/imgui.h"

class ExampleLayer : public Muto::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
	}

	~ExampleLayer() override = default;

	// Called once when the layer is attached to the layer stack
	void OnAttach() override {}

	// Called once when the layer is detached from the layer stack
	void OnDetach() override {}

	// Called every frame with the frame time
	void OnUpdate(Muto::Timestep ts) override {}

	// Render ImGui UI for this layer (optional)
	void OnImGuiRender() override {
		ImGui::Begin("Example Layer");
		ImGui::Text("Hello from ExampleLayer!");
		ImGui::End();
	}

	// Receive events (keyboard/mouse/window/etc.)
	void OnEvent(Muto::Event& e) override {}
};

class YourAppNameHere : public Muto::Application
{
public:
	YourAppNameHere() {

		PushLayer(new ExampleLayer());
	}

	~YourAppNameHere() {	}
};

Muto::Application* Muto::CreateApplication() {
	return new YourAppNameHere();
}
```

## Muto's Author: Damon S. Green II (nomad_ii_damon)
For more information about the author, please visit www.damonsgreen2.com

## Contributing
Please open issues or pull requests. 

## Licensing
> **License status:** Proprietary (subject to change)

Muto itself is not **currently** released under any specific license and is provided as-is.
Copyright © 2025 by Damon S. Green II (nomad_ii_damon).
All rights reserved unless otherwise stated.

This project contains code derived from the Hazel Engine
by TheCherno, licensed under the Apache License 2.0,
obtained through public tutorialization and source code access.

Original Hazel code and derivative works thereof are licensed
under the Apache License 2.0. Other original code in this repository
is Copyright © 2025 Damon S. Green II (nomad_ii_damon).

See the LICENSE file for details.


#### Fully-Modified File Header for Licensing
Copyright © TheCherno
Modifications Copyright © 2025 Damon S. Green II (nomad_ii_damon)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    [Apache](http://www.apache.org/licenses/LICENSE-2.0)

#### Modified File Header for Licensing
Based on Hazel Engine (Apache 2.0)
Modified by Damon S. Green II, 2025
