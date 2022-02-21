workspace "LearnOpenGL"
    configurations {"Debug", "PreRelease", "Release"}
    platforms "x64"


    -- ============================================================{Project: LearnGL}============================================================ --
    project "LearnGL"
        location "Projects/LearnGL/"
        kind "ConsoleApp"
        language "C++"
        targetdir "builds/"
        objdir "obj/%{prj.name}_%{cfg.shortname}"

        files {
            "Projects/LearnGL/src/**.h",
            "Projects/LearnGL/src/**.hpp",
            "Projects/LearnGL/src/**.cpp",
            "Projects/LearnGL/src/**.c",
        }

        includedirs {

        }


        -- Debug.
        filter {}
        filter {"configurations:Debug"}
            defines {
                "LEARN_OPENGL_DEBUG"
            }
        
        -- PreRelease (Keep timers but discard debug code).
        filter {}
        filter {"configurations:PreRelease"}
            defines {
                "LEARN_OPENGL_PRERELEASE"
            }
        
        -- Release (Discard both timers and debug code).
        filter {}
        filter {"configurations:Release"}
            defines {
                "LEARN_OPENGL_RELEASE"
            }
        

        -- ++++++++++++++++++++++++++++++++{Windows}++++++++++++++++++++++++++++++++ --



        -- Windows All Configurations.
        filter {}
        filter {"system:Windows"}
            
            defines "LEARN_OPENGL_WINDOWS"
            
            -- Windows Debug.
            filter {"configurations:Debug"}
                libdirs {

                }

                links {

                }
            
            -- Windows PreRelease.
            filter {"configurations:PreRelease"}
                libdirs {

                }

                links {

                }

            -- Windows Release.
            filter {"configurations:Release"}
                libdirs {

                }

                links {

                }
        
        -- ++++++++++++++++++++++++++++++++{Windows}++++++++++++++++++++++++++++++++ --

    -- ============================================================{Project: LearnGL}============================================================ --