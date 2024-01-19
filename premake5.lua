workspace "Snake"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "Snake"

OutputDir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

function ConfigurationsSetting()
    filter "configurations:Debug"
        defines { "_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "_RELEASE", "NDEBUG" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "_DIST", "NDEBUG" }
        runtime "Release"
        optimize "On"
        symbols "Off"
end

group "Dependencies"
    include "Snake/vendor/glfw"
    include "Snake/vendor/glad"
    include "Snake/vendor/imgui"
group ""

include "Snake"