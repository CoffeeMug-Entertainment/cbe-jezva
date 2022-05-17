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
		"thirdparty/sdl_stb_font",
		"thirdparty/Simple-SDL2-Audio/src"
	}

	files
	{
		"src/**.cpp",
		"src/*.c",
		"thirdparty/Simple-SDL2-Audio/src/audio.c"
	}

	links
	{
		"SDL2",
	}

	filter "system:windows"
		staticruntime "on"
		includedirs
		{
			"thirdparty/SDL2/include",
		}

		buildoptions
		{
			"`sdl2-config --cflags`"
		}

		linkoptions
		{
			"-static-libstdc++",
			"-static-libgcc",
			"-Wl,-Bstatic",
			"`sdl2-config --static-libs`",
			"-Wl,-Bdynamic",
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

