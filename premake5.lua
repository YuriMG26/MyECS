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

  targetdir("bin/" .. outputdir .. "/%{prj.name}")
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

  libdirs
  {
    "Vendor/raylib/lib/windows/"
  }
  
  filter { "action:vs2022" }
    toolset "msc"
    links { "winmm", "raylib" }

  filter { "action:gmake2", "system:windows" }
    links { "winmm", "raylib", "opengl32", "msvcrt", "user32", "shell32", "gdi32" }

  filter "configurations:Debug"
    symbols "On"

  filter "configurations:Release"
    optimize "On"
