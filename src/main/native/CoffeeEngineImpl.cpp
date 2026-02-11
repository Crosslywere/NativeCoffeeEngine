#include <io_coffee_engine_CoffeeEngine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cmath>
#include <iostream>

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_CoffeeEngine_Test(JNIEnv *env, jclass clazz)
{
    if (!glfwInit())
    {
        std::cout << "Test failed on init" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::string title = "Test Window will close in ";
    char timeBuffer[5];
    std::sprintf(timeBuffer, "%.1fs", 5.0f);
    GLFWwindow *window = glfwCreateWindow(800, 600, (title + timeBuffer).c_str(), nullptr, nullptr);
    if (!window)
    {
        std::cout << "Test failed on window creation" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Test failed on loading OpenGL" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    const auto start = std::chrono::steady_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        const std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
        const auto sec = duration.count();
        if (sec >= 5)
            glfwSetWindowShouldClose(window, true);
        else
            sprintf(timeBuffer, "%.1fs", std::max(5 - sec, 0.0));
        glfwSetWindowTitle(window, (title + timeBuffer).c_str());
        glClearColor(std::sin(sec), std::cos(sec), 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Tested successfully!" << std::endl;
    return true;
}