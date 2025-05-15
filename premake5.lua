workspace "Tetris"
	architecture "x64"
	startproject "Tetris"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Tetris Project --
project "Tetris"
	kind "ConsoleApp"
	language "C++"

	targetdir("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"Source",
		"ThirdParty/SFML/include"
	}

	libdirs
	{
		"ThirdParty/SFML/lib"
	}

	defines { "SFML_STATIC" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		links { "opengl32", "winmm", "gdi32", "user32", "advapi32" }

	filter "configurations:Debug"
		symbols "On"
		links { "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d" }

	filter "configurations:Release"
		optimize "On"
		links { "sfml-graphics-s", "sfml-window-s", "sfml-system-s" }