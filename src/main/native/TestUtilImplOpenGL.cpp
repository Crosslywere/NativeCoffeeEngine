#include <io_coffee_engine_test_TestUtil.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define TOTAL_RUNTIME 5.0

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_test_TestUtil_TestOpenGL(JNIEnv *env, jclass)
{
    jclass runtimeError = env->FindClass("java/lang/RuntimeException");
    if (!glfwInit())
    {
        env->ThrowNew(runtimeError, "Failed on glfwInit");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Testing OpenGL (5s)", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        env->ThrowNew(runtimeError, "Failed to create window");
        return false;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        env->ThrowNew(runtimeError, "Failed to load OpenGL function pointers");
        return false;
    }
    while (!glfwWindowShouldClose(window))
    {
        float time = glfwGetTime();
        if (time >= TOTAL_RUNTIME)
        {
            glfwSetWindowShouldClose(window, true);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(std::sin(time), std::cos(time), time / TOTAL_RUNTIME, 1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (glfwGetTime() < TOTAL_RUNTIME)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        env->FatalError("Closed window before test concluded!");
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return true;
}
