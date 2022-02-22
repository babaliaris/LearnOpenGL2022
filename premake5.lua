-- cmake -S path/to/glfw -B path/to/build -D BUILD_SHARED_LIBS=OFF


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
 
 --- Check if a directory exists
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



--Check if Program Exists.
function CheckIfProgramExists(program_name)

    --If Windows.
    if (CheckOS() == "Windows") then

        local handle = io.popen(program_name.." 2>&1") -- Try to run the command and redirect the output to stderr.
        local output = handle:read("*all") -- Read stderr output.

        -- If "is not recognized as an internal or external command" exists, then the program could not be run.
        if ( string.match(output, "is not recognized as an internal or external command") ) then
            return false
        end
    
    --Linux.
    else
        print("CheckIfProgramExists() NOT implemented for Linux.")
        return false
    end

    --Program found.
    return true
end

 -- ||||||||||||||||||||||||||||||Some Helpful Functions|||||||||||||||||||||||||||||| --




-- Clean all the Cmake stuff.
function Clean()

    -- Clean the cmake gen files and any compiled stuff.
    if (_ACTION == "clean") then
        
        --Print a message that we are cleaning stuff.
        print("=============================Cleaning=============================")

        -- WINDOWS: Clean glfw.
        if ( CheckOS() == "Windows" and DirExists("External\\glfw\\build")) then
            os.execute("rmdir External\\glfw\\build /s /q")
            os.execute("rmdir libs /s /q")
        end

        -- Exit after finish cleaning.
        os.exit()
    end
end



-- Cmake and Compile GLFW.
-- (ASSUMES THAT CMAKE && msbuild ARE IN THE PATH ENV VARIABLE)
function CompileGLFW()
   
    -- If Windows and glfw has not been build yet.
    if ( CheckOS() == "Windows" and not DirExists("External\\glfw\\build") ) then
        os.execute("cmake -S External\\glfw -B External\\glfw\\build -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF") --Cmake the project files.
        os.execute("cd External\\glfw\\build && msbuild GLFW.sln /p:Configuration=Debug") --Build Debug.
        os.execute("cd External\\glfw\\build && msbuild GLFW.sln /p:Configuration=Release") --Build Release.
        os.execute("xcopy External\\glfw\\build\\src\\Debug\\glfw3.lib libs\\debug\\") --Copy the debug glfw.lib to libs/debug
        os.execute("xcopy External\\glfw\\build\\src\\Debug\\glfw3.pdb libs\\debug\\") --Copy the debug glfw.pdb to libs/debug
        os.execute("xcopy External\\glfw\\build\\src\\Release\\glfw3.lib libs\\release\\") --Copy the release glfw.lib to libs/release

    -- If Linux and glfw has not been build yet.
    elseif ( CheckOS() == "Linux" and not DirExists("External/glfw/build") ) then
        print("[Warning] GLFW build on LINUX hasn't been implemented yet...")

    -- GLFW already compiled.
    else
        print("[Warning] The directory: External/glfw/build, already exists. Run premake5 clean, if you want to rebuild glfw.")
    end
end


--Check if cmake can be run.
if ( not CheckIfProgramExists("cmake") ) then
    print("cmake was not found. Make sure it is installed and set in the PATH environment variable.")
    print("Aborting...")
    os.exit()
end

--Check if msbuild.exe can be run.
if ( CheckOS() == "Windows" and not CheckIfProgramExists("msbuild") ) then
    print("msbuild.exe was not found. Make sure it is installed and set in the PATH environment variable.")
    print("Aborting...")
    os.exit()
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
                    "libs/debug"
                }
            
            -- Windows PreRelease.
            filter {"configurations:PreRelease"}
                libdirs {
                    "libs/release"
                }

            -- Windows Release.
            filter {"configurations:Release"}
                libdirs {
                    "libs/release"
                }
        
        -- ++++++++++++++++++++++++++++++++{Windows}++++++++++++++++++++++++++++++++ --

    -- ============================================================{Project: LearnGL}============================================================ --