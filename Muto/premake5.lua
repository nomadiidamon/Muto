project "Muto"
	location "Muto"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vzpch.h"
	pchsource "src/vzpch.cpp"

	files 
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	filter "files:Muto/vendor/imgui/backends/**.cpp"
		flags { "NoPCH" }
	filter "files:vendor/ImGuizmo/ImGuizmo.cpp"
		flags { "NoPCH" }
	filter {}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.Resources}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"

    buildoptions { "/utf-8" }


	defines
	{
		"VZ_PLATFORM_WINDOWS", 
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

	filter "configurations:Debug"
		defines "VZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VZ_DIST"
		runtime "Release"
		optimize "on"

