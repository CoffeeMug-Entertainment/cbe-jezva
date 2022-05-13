 workspace "BeanPong"
 	architecture "x64"

 	configurations
    {
        "Debug",
        "Release"
    }

include "../../premake5.lua"

project "BeanPong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

	files
	{
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"../../include",
		"../../thirdparty/json/single_include",
		"../../thirdparty/Xoshiro/"
	}

	libdirs
    {
    	"../../lib/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/CoffeeBean"
    }

    links
	{
		"CoffeeBean",
		"SDL2",
		"SDL2_image",
		"SDL2_ttf",
		"SDL2_mixer"

	}


	filter "system:windows"
		includedirs
		{
			"../../thirdparty/SDL2/include",
			"../../thirdparty/SDL_image",
			"../../thirdparty/SDL2_ttf"
		}

     	links
     	{
     		"mingw32",
     		"SDL2main"
     	}
		 
		defines
		{
			"_WIN32"
		}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


    postbuildcommands
    {
    	"{COPY} %{cfg.targetdir}/%{prj.name} ./%{prj.name}"
    }
