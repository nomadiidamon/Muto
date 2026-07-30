project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Muto/vendor/spdlog/include",
		"%{wks.location}/Muto/src",
		"%{wks.location}/Muto/vendor",
		"%{wks.location}/Muto/vendor/imgui",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Muto",
	}

	filter "system:windows"
		systemversion "latest"

    buildoptions { "/utf-8" }


		defines
		{
			"MU_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "MU_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "MU_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "MU_DIST"
			runtime "Release"
			optimize "on"
