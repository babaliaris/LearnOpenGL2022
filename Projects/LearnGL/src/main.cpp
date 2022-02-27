#include <pch.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <core/gl/glcall.h>
#include <core/core.h>
#include <core/logger.h>
#include <core/gl/vertexArray.h>
#include <core/gl/vertexBuffer.h>
#include <core/gl/shader.h>
#include <core/gl/texture.h>

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


    float data[] = {

        //Positions             Texture Coordinates.
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,

        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f
    };


    LearnOpenGL::VertexBuffer *vbo = new LearnOpenGL::VertexBuffer(data, sizeof(data));
    vbo->pushLayout<float>(3, false, "Positions");
    vbo->pushLayout<float>(2, false, "Texture Coordinates");

    LearnOpenGL::VertexArray *vao = new LearnOpenGL::VertexArray(*vbo);

    LearnOpenGL::Shader* shader = new LearnOpenGL::Shader(LEARN_OPENGL_RELATIVE_PATH("src/resources/shaders/test_textured_quad.glsl"));
    shader->setInt("texSlot", 0);

    LearnOpenGL::Texture* texture = new LearnOpenGL::Texture(LEARN_OPENGL_RELATIVE_PATH("src/resources/images/test.jpg"));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall( glClear(GL_COLOR_BUFFER_BIT) );

        texture->bind();
        shader->Bind();
        vao->bind();
        GLCall( glDrawArrays(GL_TRIANGLES, 0, vbo->getVertexCount() ) );

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete vao;
    delete vbo;
    delete shader;
    delete texture;


    glfwTerminate();
    return 0;
}