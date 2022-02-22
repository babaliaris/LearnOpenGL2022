#include "glcall.h"
#include <glad/glad.h>
#include <iostream>
#include <sstream>

namespace LearnOpenGL
{
	void CleanAllOpenGLErrors()
	{
		while ( glGetError() );
	}


	void RetrieveAllOpenGLErrors(const char* file, unsigned int line)
	{
		while ( GLenum error = glGetError() )
		{
			std::cout << "[GLError: " << error << "]" << std::endl;
			std::cout << "\tAt File: " << file << std::endl;
			std::cout << "\tAt Line: " << line << std::endl << std::endl;
		}
		
	}
}