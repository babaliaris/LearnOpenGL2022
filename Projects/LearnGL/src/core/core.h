#pragma once
#include <iostream>

//LEARN_OPENGL_WINDOWS
//LEARN_OPENGL_LINUX
//LEARN_OPENGL_DEBUG
//LEARN_OPENGL_PRERELEASE
//LEARN_OPENGL_RELEASE

#define LEARN_OPENGL_COND(cond, code)\
{\
	if ( (cond) )\
	{\
		code; \
	}\
}


//If we are running through Visual Studio, we are already relative to the project root.
#ifdef _MSC_VER
	#define LEARN_OPENGL_RELATIVE_PATH(path) path


//If we are running through the command line, concatenate the path relative to the project's root dir.
#else
	#define LEARN_OPENGL_RELATIVE_PATH(path) std::string("Projects/LearnGL") + #path

#endif