-- msbuild GLFW.sln /p:Configuration=Release
-- cmake -S path/to/glfw -B path/to/build -D BUILD_SHARED_LIBS=OFF
-- cmake -S path/to/glfw -B path/to/build -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF

-- NEVER CHANGE THESE!!! For windows I'm forced to hard code some paths to rmdir
__LIBS_DIR__        = path.join("libs", "")
__LIBS_GLFWDIR__    = path.join(__LIBS_DIR__, "glfw")



-- ||||||||||||||||||||||||||||||Some Helpful Functions|||||||||||||||||||||||||||||| --

-- Check OS.
function CheckOS() 
    if ( package.config:sub(1,1) == "\\" ) then
        return "Windows"
    else
        return "Linux"
    end
end

-- Check if a file or directory exists in this path
function FileExists(file)
    local ok, err, code = os.rename(file, file)
    if not ok then
       if code == 13 then
          -- Permission denied, but it exists
          return true
       end
    end
    return ok, err
 end
 
 --- Check if a directory exists in this path
 function DirExists(path)
    -- "/" works on both Unix and Windows
    return FileExists(path.."/")
 end


 -- Ask A Question.
 function AskQuestion(question)
    local answer
    repeat
        io.write(question.."(y/n): ")
        io.flush()
        answer=io.read()
    until answer=="y" or answer=="n"

    return answer
end

 -- ||||||||||||||||||||||||||||||Some Helpful Functions|||||||||||||||||||||||||||||| --




-- Clean all the Cmake stuff.
function Clean()

    -- Clean the cmake gen files and any compiled stuff.
    if (_ACTION == "clean") then
        
        --Print a message that we are cleaning stuff.
        print("=============================Cleaning=============================")

        -- WINDOWS: Clean glfw.
        if ( CheckOS() == "Windows" and DirExists(__LIBS_GLFWDIR__)) then
            os.execute("rmdir libs\\glfw /s /q")
        end

        -- Exit after finish cleaning.
        os.exit()
    end
end



-- Cmake and Compile GLFW.
-- (ASSUMES THAT CMAKE && msbuild ARE IN THE PATH ENV VARIABLE)
function CompileGLFW()
   
    -- If Windows and glfw has not been build yet.
    if ( CheckOS() == "Windows" and not DirExists(__LIBS_GLFWDIR__) ) then
        os.execute("cmake -S External/glfw -B libs/glfw -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF") --Cmake the project files.
        os.execute("cd "..__LIBS_GLFWDIR__.." && msbuild GLFW.sln /p:Configuration=Debug") --Build Debug.
        os.execute("cd "..__LIBS_GLFWDIR__.." && msbuild GLFW.sln /p:Configuration=Release") --Build Release.

    -- If Linux and glfw has not been build yet.
    elseif ( CheckOS() == "Linux" and not DirExists(__LIBS_GLFWDIR__) ) then
        print("[Warning] GLFW build on LINUX hasn't been implemented yet...")

    -- GLFW already compiled.
    else
        print("[Warning] The directory: "..__LIBS_GLFWDIR__..", already exists. Run premake5 clean, if you want to rebuild glfw.")
    end
end



-- Some Information To The User (DO NOT SHOW THIS IF CLEANING).
if ( _ACTION ~= "clean" ) then
print("Before we continue with project files generation (The following are needed in order to build and compile external dependencies):")
print("Make sure that:")
print("    1) All OS's  : Cmake is installed and set in the Environment Path Variable")
print("    2) On Windows: msbuild.exe bin directory is set in the Environment Path Variable (usually the path is: C:\\Program Files\\Microsoft Visual Studio\\<year>\\Community\\Msbuild\\Current\\Bin)")
print("    3) On Linux  : make and autotools are installed and set in the Environment Path Variable")
print("If you are getting linking errors, probably some external libs failed to compile. See the output of this script to figure out why.")
print("You can always run premake5 clean and then premake5 <action> to rebuild any depedencies and see the compilation output.")

    -- Ask if the user wants to continue with the script's execution.
    if ( AskQuestion("\nDo you want to continue with the project files generation?") == "n" ) then
        os.exit()
    end
end


--First check if cleaning was instructed.
Clean()

--Compile any Cmake dependent external library (If cleaning, skip this step).
if ( _ACTION ~= "clean" ) then
    CompileGLFW()
end





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
            "Projects/LearnGL/src/",
            "Projects/LearnGL/src/external/glad/include/",
            "Projects/LearnGL/src/external/stb_image/include/",
            "External/glfw/include/"
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

            links {
                "glfw3",
                "opengl32"
            }
            
            -- Windows Debug.
            filter {"configurations:Debug"}
                libdirs {
                    "libs/glfw/src/Debug"
                }
            
            -- Windows PreRelease.
            filter {"configurations:PreRelease"}
                libdirs {
                    "libs/glfw/src/Release"
                }

            -- Windows Release.
            filter {"configurations:Release"}
                libdirs {
                    "libs/glfw/src/Release"
                }
        
        -- ++++++++++++++++++++++++++++++++{Windows}++++++++++++++++++++++++++++++++ --

    -- ============================================================{Project: LearnGL}============================================================ --