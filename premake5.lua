workspace "MyECS"
  architecture "x64"

  configurations
  {
    "Debug",
    "Release"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MyECS"
  -- location "MyECS"
  language "C++"
  cppdialect "C++20"
  toolset "clang"
  kind "ConsoleApp"
  symbols "On"

  target_dir = "bin/" .. outputdir .. "/%{prj.name}"
  targetdir(target_dir)
  objdir("bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "**.h",
    "**.cpp"
  }

  includedirs
  {
    "Vendor/raylib/include/",
    "Vendor/entt/"
  }

  filter { "system:windows" } 
    libdirs
    {
      "Vendor/raylib/lib/windows/"
    }

  filter { "system:linux" }
    links { "raylib" }
    libdirs
    {
      "vendor/raylib/lib/linux/amd64/"
    }
    linkoptions { "-R ../../../vendor/raylib/lib/linux/amd64/" }

  -- filter { "system: linux", "architecture:x86_64" }

  filter { "action:not xcode4" }
    disablewarnings { "format-security" }
  
  filter { "action:vs2022" }
    toolset "msc"
    links { "winmm", "raylib" }

  filter { "action:gmake2", "system:windows" }
    links { "winmm", "raylib", "opengl32", "msvcrt", "user32", "shell32", "gdi32" }

  filter "configurations:Debug"
    debugdir(target_dir)
    symbols "On"
    linkoptions { '-g' }

  filter "configurations:Release"
    optimize "On"
