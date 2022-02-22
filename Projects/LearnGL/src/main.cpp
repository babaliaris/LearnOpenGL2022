#include <pch.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <core/gl/glcall.h>
#include <core/core.h>
#include <core/logger.h>
#include <core/shader.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cout << "GLAD faild to initialize" << std::endl;
    }

    //Initialize the logger.
    LearnOpenGL::Logger::Init();

    LearnOpenGL::Shader *shader = new LearnOpenGL::Shader(LEARN_OPENGL_RELATIVE_PATH("src/resources/test_shader.glsl"));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall( glClear(GL_COLOR_BUFFER_BIT) );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    delete shader;
    glfwTerminate();
    return 0;
}