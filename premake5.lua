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
		"thirdparty/Xoshiro/",
		"thirdparty/stb",
		"thirdparty/sdl_stb_font"
	}

	files
	{
		"src/**.cpp",
		"src/*.c"
	}

	links
	{
		"SDL2",
		"SDL2_mixer"

	}

	filter "system:windows"
		staticruntime "on"
		includedirs
		{
			"thirdparty/SDL2/include",
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
		
	filter "configurations:Debug"
		 runtime "Debug"
		 symbols "on"

	 filter "configurations:Release"
		 runtime "Release"
		 optimize "on"

