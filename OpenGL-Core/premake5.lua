project "OpenGL-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/imgui",
        "vendor/glm",
        "vendor",
    }

    links {
        "opengl32.lib",
        "GLFW",
        "Glad",
        "ImGui",
        "stb"
    }

    targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir("../bin-int/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { }

    ConfigurationsSetting()