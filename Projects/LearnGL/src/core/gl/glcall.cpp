#include <pch.h>
#include "glcall.h"
#include <glad/glad.h>
#include <core/logger.h>

namespace LearnOpenGL
{
	//Get Open GL Error Meaning.
	std::string GetOpenGLErrorMeaning(GLenum gl_error)
	{
		//Switch the GLEnum error code.
		switch (gl_error)
		{
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";

		case GL_INVALID_VALUE:
			return "GL_INVALID_VALUE";

		case GL_INVALID_OPERATION:
			return "GL_INVALID_OPERATION";

		case GL_OUT_OF_MEMORY:
			return "GL_OUT_OF_MEMORY";

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "GL_INVALID_FRAMEBUFFER_OPERATION";

		default:
			return "Uknown Error";
		}
	}

	
	//Clear All OpenGL Errors.
	void CleanAllOpenGLErrors()
	{
		while ( glGetError() );
	}


	//Retrieve and LOG ALL OpenGL Errors.
	void RetrieveAllOpenGLErrors(const char* file, unsigned int line)
	{
		while ( GLenum error = glGetError() )
		{
			LEARN_OPENGL_ERROR(": [OpenGL Error: {} -> {}]\n\tIn File: {}\n\tAt Line: {}\n", error, GetOpenGLErrorMeaning(error), file, line);
		}
		
	}
}