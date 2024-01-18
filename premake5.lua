workspace "Pico"
    configurations {"Debug", "Release"}

    project "Sandbox"
        kind "ConsoleApp"
        language "C"

        files {
            "./src/sandbox/sandbox.c"
        }

        includedirs {
            "include",
            "vendor/include"
        }

        links {
            "Engine",
            "glfw3",
            "m",
            "Glad"
        }

        libdirs {
            "vendor"
        }

        filter "configurations:Release"
            defines {"NDEBUG"}
            optimize "On"

        filter "configurations:Debug"
            defines {"DEBUG"}
            optimize "Off"
            symbols "On"

    project "Engine"
        kind "StaticLib"
        language "C"

        files {
            "./src/engine/engine.c",
            "src/engine/maths.c",
            "src/engine/renderer.c",
            "src/engine/utils.c",
            "src/engine/stb_image.c",
            "src/engine/image.c"
        }

        includedirs {
            "include",
            "vendor/include"
        }

        links {
            "glfw3",
            "m",
            "Glad"
        }

        libdirs {
            "vendor"
        }

        filter "configurations:Debug"
            defines {"DEBUG"}
            optimize "Off"
            symbols "On"