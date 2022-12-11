workspace "Dictionary"
   configurations { "Debug", "Release" }

project "Dictionary"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "./include/**" }
    libdirs { "./lib" }
    links { "m", "GLEW", "GL", "glfw", "curl", "json-c", "dotenv" }

    files { "lib_src/**.c", "src/**.h", "src/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"