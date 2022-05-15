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
		"../../thirdparty/Xoshiro/",
		"../../thirdparty/stb",
		"../../thirdparty/sdl_stb_font"
	}

	libdirs
    {
    	"../../lib/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/CoffeeBean"
    }

    links
	{
		"CoffeeBean",
		"SDL2",
	}


	filter "system:windows"
		staticruntime "on"
		includedirs
		{
			"../../thirdparty/SDL2/include",
		}

     	links
     	{
     		"mingw32",
     		"SDL2main"
     	}
		
		buildoptions
		{
			"`sdl2-config --cflags --static-libs`",
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
