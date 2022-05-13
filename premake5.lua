project "CoffeeBean" 

	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	--targetdir = ("lib/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	--objdir = ("obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

	includedirs
	{
		"include",
		--"thirdparty/SDL2/include",
		--"thirdpartySDL2_ttf",
		"thirdparty/json/single_include",
		"thirdparty/Xoshiro/"
	}

	files
	{
		"src/**.cpp",
		"src/*.c"
	}

	links
	{
		"SDL2",
		"SDL2_image",
		"SDL2_ttf",
		"SDL2_mixer"

	}

	filter "system:windows"
		staticruntime "on"
		includedirs
		{
			"thirdparty/SDL2/include",
			"thirdparty/SDL_image",
			"thirdparty/SDL2_ttf"
		}

		buildoptions
		{
			"`sdl2-config --cflags --static-libs`"
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

