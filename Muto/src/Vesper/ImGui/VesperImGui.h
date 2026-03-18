#pragma once
/// @file VesperImGui.h
/// @author Damon S. Green II
/// @brief Defines the VesperImGui class, which provides functionality for displaying information about the Vesper engine using ImGui. This includes details about the engine's features, roadmap, and controls.

#include "imgui/imgui.h"

namespace Vesper {

	/// @brief Function to display information about the Vesper engine using ImGui. This includes details about the engine's features, roadmap, and controls.
	static void DisplayVesperInfo_ImGui()
	{
		ImGui::Begin("Vesper Info");

		if (ImGui::TreeNode("About Vesper"))
		{
			ImGui::Text("Vesper Engine");
			ImGui::Text("Version: 0.1.0");
			ImGui::Text("Author: Damon Green II");
			ImGui::Text("GitHub: https://github.com/nomadiidamon/Vesper");
			ImGui::Separator();

			ImGui::Text("Status: ");
			ImGui::Text("\tEarly Development of API and 2D Renderer");
			ImGui::Separator();

			ImGui::TextWrapped("Vesper is a cross-platform game engine currently in early development. The engine is being built from the ground up with a focus on modularity, performance, and ease of use. The goal of Vesper is to provide developers with a powerful and flexible toolset for creating games and interactive applications.");
			ImGui::Separator();

			if (ImGui::TreeNode("Controls:"))
			{
				ImGui::Text("\tWASD: Move Camera");
				ImGui::Text("\tQ/E: Rotate Camera (if enabled {see settings})");
				ImGui::Text("\tScroll Wheel: Zoom Camera");
				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::TreeNode("RoadMap")) {

				if (ImGui::TreeNode("Current Features:"))
				{
					ImGui::Text("\t- Cross-Platform Design");
					ImGui::Text("\t\t- Currently Windows only");
					ImGui::Text("\t- OpenGL Renderer");
					ImGui::Text("\t- Orthographic Camera");
					ImGui::Text("\t- Shader System");
					ImGui::Text("\t- Texture Loading");
					ImGui::Text("\t- ImGui Integration");
					ImGui::Text("\t\t- Current settings panel adjusts camera parameters!");

					ImGui::TreePop();
				}
				ImGui::Separator();

				if (ImGui::TreeNode("In Progress:"))
				{
					ImGui::Text("\t- 2D Rendering Features");
					ImGui::Text("\t\t- Sprites");
					ImGui::Text("\t\t- Sprite Sheets");
					ImGui::Text("\t\t- Animation");
					ImGui::TreePop();
				}
				ImGui::Separator();

				if (ImGui::TreeNode("Planned Features:"))
				{
					ImGui::Text("\t- Vulkan Renderer");
					ImGui::Text("\t- 2D Editor");
					ImGui::Text("\t- 2D Particles");
					ImGui::Text("\t- Audio");
					ImGui::Text("\t- Timelining");
					ImGui::Text("\t- Video Playback");
					ImGui::Text("\t- 3D Renderer");
					ImGui::Text("\t- 3D Particles");
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
		ImGui::End();
	}


}