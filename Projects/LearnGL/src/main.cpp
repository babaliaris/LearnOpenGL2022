#include <pch.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/gl/glcall.h>
#include <core/core.h>
#include <core/logger.h>
#include <core/Layer.h>

#include <Layers/TestLayer.h>


namespace LearnOpenGL
{
    class App
    {

    public:
        App() : m_Window(nullptr)
        {
            //Initialize the logger.
            Logger::Init();

            /* Initialize the library */
            if (!glfwInit())
            {
                LEARN_OPENGL_ERROR("GLFW failed to initialize");
                return;
            }

            /* Create a windowed mode window and its OpenGL context */
            m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
            if (!m_Window)
            {
                LEARN_OPENGL_ERROR("GLFW failed to create a window.");
                glfwTerminate();
                return;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(m_Window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                LEARN_OPENGL_ERROR("GLAD failed to initialize");
                glfwTerminate();
                return;
            }

            //Everything initialized successfully.
            m_runSucces = true;
        }





        ~App()
        {
            for (Layer* layer : m_layers)
            {
                delete layer;
            }

            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }





        void Run()
        {
            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(m_Window))
            {
                /* Render here */
                GLCall(glClear(GL_COLOR_BUFFER_BIT));



                //------------------------Handle Layers------------------------//
                for (Layer* layer : m_layers)
                {
                    //Call start only once.
                    if (layer->m_Started == false)
                    {
                        layer->OnStart();
                        layer->m_Started = true;
                    }

                    //Start calling update, one frame after OnStart()
                    //to insure initialization of all layers.
                    else
                    {
                        layer->OnUpdate();
                    }
                }
                //------------------------Handle Layers------------------------//



                /* Swap front and back buffers */
                glfwSwapBuffers(m_Window);

                /* Poll for and process events */
                glfwPollEvents();
            }
        }



        void pushLayer(Layer *layer)
        {
            m_layers.push_back(layer);
        }


        bool GetRunSuccess()
        {
            return m_runSucces;
        }





    private:
        GLFWwindow* m_Window;
        bool m_runSucces = false;
        std::vector<Layer*> m_layers;


    };
}


int main(void)
{

    TestLayer *testLayer = new TestLayer();

    //Create the App.
    LearnOpenGL::App* app = new LearnOpenGL::App();

    //PUSH LAYER HERE.
    app->pushLayer(testLayer);

    //Run the app.
    if (app->GetRunSuccess())
        app->Run();

    //Delete the app.
    delete app;

    return 0;
}