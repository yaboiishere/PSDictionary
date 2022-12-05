workspace "Dictionary"
   configurations { "Debug", "Release" }

project "Dictionary"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "./include/**" }
    libdirs { "./lib" }
    links { "m", "GLEW", "GL", "glfw", "curl", "json-c", "dotenv" }

    files { "src/**.h", "src/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"