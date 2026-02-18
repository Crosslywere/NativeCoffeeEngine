#include <io_coffee_engine_test_TestUtil.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stdexcept>
#define TOTAL_RUNTIME 5.0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class OpenGLApp
{
public:
    void run()
    {
        initWindow();
        mainLoop();
        cleanup();
    }

    const double getTime() const
    {
        return time;
    }

private:
    void initWindow()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize glfw");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Testing OpenGL (5s)", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create window!");
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cleanup();
            throw std::runtime_error("Failed to load OpenGL function pointers");
        }
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            time = glfwGetTime();
            if (time >= TOTAL_RUNTIME)
            {
                glfwSetWindowShouldClose(window, true);
            }
            glClearColor(std::sin(time), std::cos(time), time / TOTAL_RUNTIME, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    GLFWwindow *window;
    double time = 0.0;
};

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_test_TestUtil_TestOpenGL(JNIEnv *env, jclass)
{
    OpenGLApp app;
    try
    {
        app.run();
    }
    catch (std::exception e)
    {
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what());
        return false;
    }
    return app.getTime() >= TOTAL_RUNTIME;
}
