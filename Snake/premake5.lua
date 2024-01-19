project "Snake"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    files { "src/**.h", "src/**.cpp" }

    includedirs {
        "src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/imgui/include"
    }

    links {
        "opengl32.lib",
        "GLFW",
        "Glad",
        "ImGui"
    }

    targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir("../bin-int/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { }

    ConfigurationsSetting()