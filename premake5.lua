include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Muto"
	architecture "x64"

	startproject "Sandbox"

	configurations 
	{ 
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["entt"] = "%{wks.location}/Muto/vendor/entt/include"
IncludeDir["Glad"] = "%{wks.location}/Muto/vendor/Glad/include"
IncludeDir["GLFW"] = "%{wks.location}/Muto/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Muto/vendor/glm"
IncludeDir["ImGui"] = "%{wks.location}/Muto/vendor/imgui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Muto/vendor/ImGuizmo"
IncludeDir["stb_image"] = "%{wks.location}/Muto/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Muto/vendor/yaml-cpp/include"
IncludeDir["Resources"] = "%{wks.location}/Resources"

group "Dependencies"
	include "Muto/vendor/GLFW"
	include "Muto/vendor/Glad"
	include "Muto/vendor/imgui"
	include "Muto/vendor/yaml-cpp"

group ""


group "Core"
	include "Muto"
group ""

group "Misc"
	include "Sandbox"
group ""
