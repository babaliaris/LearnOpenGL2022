#include <pch.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <core/gl/glcall.h>
#include <core/core.h>
#include <core/logger.h>
#include <core/gl/vbo.h>
#include <core/gl/vao.h>
#include <core/gl/shader.h>

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


    float data[18] = {

        //Positions
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    LearnOpenGL::Vao *vao = new LearnOpenGL::Vao();
    LearnOpenGL::Vbo *vbo = new LearnOpenGL::Vbo(data, 18);

    vao->Bind();
    vbo->Bind();

    vbo->PushLayout({ 3, sizeof(float) * 6, LearnOpenGL::LayoutTypeE::FLOAT });
    vbo->PushLayout({ 3, sizeof(float) * 6, LearnOpenGL::LayoutTypeE::FLOAT });

    vao->Ubind();
    vbo->Unbind();


    LearnOpenGL::Shader* shader = new LearnOpenGL::Shader(LEARN_OPENGL_RELATIVE_PATH("src/resources/test_shader.glsl"));



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall( glClear(GL_COLOR_BUFFER_BIT) );

        shader->Bind();
        vao->Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete vao;
    delete vbo;

    glfwTerminate();
    return 0;
}