project "Snake"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "%{wks.location}/OpenGL-Core/src",
        "%{wks.location}/OpenGL-Core/vendor/glfw/include",
        "%{wks.location}/OpenGL-Core/vendor/glad/include",
        "%{wks.location}/OpenGL-Core/vendor/imgui",
        "%{wks.location}/OpenGL-Core/vendor/glm",
        "%{wks.location}/OpenGL-Core/vendor",
    }

    links {
        "OpenGL-Core"
    }

    targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir("../bin-int/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { }

    ConfigurationsSetting()