# Muto

Muto is a lightweight graphics application inspired by TheCherno's Game Engine Architecture series for the Hazel engine.  
It provides a renderer, scene & entity system, editor UI, input handling, and utilities to build simple games and interactive applications in C++ (C++17).

## Quick overview

- Language: C++17
- Platforms: Windows (Visual Studio solution can be generated via script)
  - Planned: Linux, macOS
- Build system: Premake5
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

## Getting started (clone + third-party libs)

```bash
git clone --recursive https://github.com/nomadiidamon/Muto <desiredLocation>
```

## Build (Visual Studio 2022)

1. Run the 'Win-GenProjects.bat' script from the repository root 'Muto/scripts/Win-GenProjects.bat' to generate the Visual Studio solution file (`.sln`).
	- This runs Premake5 which is located in 'Muto/Vendor/bin/premake'.
2. Open the solution in Visual Studio 2022.
3. Select the desired configuration (e.g. `Debug` or `Release`) and platform (`x64`).
4. Build and run.

Troubleshooting:
- Ensure the Windows SDK and Visual C++ toolset for VS2022 are installed.
- If include or linker errors appear, confirm vendor project builds (GLFW, Glad, ImGui, etc.) and that project dependencies are set correctly.
- For unresolved externals, confirm platform (x86/x64) consistency across projects.

## Documentation
Documentation for this project was auto generated using Doxygen version 1.16.1 and can be found at the following: 

	[Muto Documentation](https://nomadiidamon.github.io/Muto/)

## Contributing
For full contributing guidlines view [Contributing Guidelines](CONTRIBUTING.md).

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
