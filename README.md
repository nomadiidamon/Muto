# Muto

Muto is a lightweight graphics application inspired by TheCherno's Game Engine Architecture series for the Hazel engine.  
It provides a renderer, scene & entity system, editor UI, input handling, and utilities to build simple games and interactive applications in C++ (C++17).

## Quick overview

- Language: C++17
- Platforms: Windows and Linux
  - Planned: macOS
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

## Setup

### Windows

1. Run `scripts/Win-GenProjects.bat` from the repository root to generate the Visual Studio solution file (`.sln`).
2. Open the solution in Visual Studio 2022.
3. Select the desired configuration (e.g. `Debug` or `Release`) and platform (`x64`).
4. Build and run.

Requirements:
- Windows SDK and Visual C++ toolset for Visual Studio 2022.
- Git submodules initialized with `git clone --recursive`.

### Linux

On Fedora, install the compiler, Premake, OpenGL/X11 development libraries, and XDG Desktop Portal support:

```bash
sudo dnf install -y gcc-c++ gdb make premake \
  mesa-libGL-devel libX11-devel libXrandr-devel libXinerama-devel \
  libXcursor-devel libXi-devel libportal-devel
```

Generate the GNU Make projects and build the Debug Sandbox:

```bash
./scripts/Linux-GenProjects.sh
make config=debug Sandbox
./bin/Debug-linux-x86_64/Sandbox/Sandbox
```

The convenience script performs the build and launch steps in one command:

```bash
./scripts/Linux-Run.sh
```

Use `release` or `dist` as an optional argument to select another configuration:

```bash
./scripts/Linux-Run.sh release
```

The Linux editor uses XDG Desktop Portal for Open and Save dialogs. A KDE, GTK, or other compatible portal backend must be running in the desktop session. The current implementation has been tested with KDE Plasma and `xdg-desktop-portal-kde`.

## Documentation
Documentation for this project was auto generated using Doxygen version 1.16.1 and can be found at the following: 

https://nomadiidamon.github.io/Muto/

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

https://www.apache.org/licenses/LICENSE-2.0


#### Modified File Header for Licensing
Based on Hazel Engine (Apache 2.0)
Modified by Damon S. Green II, 2025
