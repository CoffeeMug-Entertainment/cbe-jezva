project "CoffeeBean" 

	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

	--targetdir = ("lib/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	--objdir = ("obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

	sysincludedirs
	{
		"thirdparty/SDL2/include",
		"thirdparty/json/single_include",
		"thirdparty/Xoshiro/",
		"thirdparty/stb",
		"thirdparty/sdl_stb_font",
		"thirdparty/Simple-SDL2-Audio/src"
	}

	includedirs
	{
		"include"
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

	filter {"system:linux"}
		defines
		{
			"CBE_LINUX"
		}

	filter {"system:windows"}
		staticruntime "on"

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
			"CBE_WINDOWS",
			"_WIN32",
		}
		
	filter "configurations:Debug"
		 runtime "Debug"
		 symbols "on"

		 defines
		 {
			 "CBE_DEBUG"
		 }

	 filter "configurations:Release"
		 runtime "Release"
		 optimize "on"

		 defines
		 {
			 "CBE_RELEASE"
		 }

