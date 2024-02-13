project "stb"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files {
        "**.h",
        "**.cpp"
    }

    targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir("../bin-int/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"

    ConfigurationsSetting()