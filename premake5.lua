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
            "m"
        }

        libdirs {
            "vendor"
        }

    project "Engine"
        kind "StaticLib"
        language "C"

        files {
            "./src/engine/engine.c",
            "src/engine/maths.c"
        }

        includedirs {
            "include",
            "vendor/include"
        }

        links {
            "glfw3",
            "m"
        }

        libdirs {
            "vendor"
        }