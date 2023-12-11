-- premake5.lua
workspace "Uno Game"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Uno-App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Uno-Core/Build-Core.lua"
group ""

include "Uno-App/Build-App.lua"