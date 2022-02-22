#pragma once

namespace LearnOpenGL
{
	void CleanAllOpenGLErrors();
	void RetrieveAllOpenGLErrors(const char *file, unsigned int line);
}



#ifdef LEARN_OPENGL_DEBUG
	#define GLCall(func) LearnOpenGL::CleanAllOpenGLErrors(); func; LearnOpenGL::RetrieveAllOpenGLErrors(__FILE__, __LINE__)

#else
	#define GLCall(func)

#endif