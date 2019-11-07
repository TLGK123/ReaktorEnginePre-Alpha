-- premake5.lua
workspace "CSharpDLL"
   configurations { "Debug", "Release" }

project "CSharpDLL"
   kind "SharedLib"
   language "C#"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.cs", "**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"