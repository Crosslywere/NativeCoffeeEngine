#include "io_coffee_engine_CoffeeEngine.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <cmath>
#include <iostream>

inline const std::string utos(unsigned int i) {
    char num = '0' + abs(i % 10);
    const char* pnum = &num;
    if (i >= 10) {
        return utos(i / 10) + std::string(pnum);
    }
    return std::string(pnum);
}

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_CoffeeEngine_Test(JNIEnv *env, jclass clazz)
{
    if (!glfwInit()) {
        std::cout << "Test failed on init" << std::endl;
        return false;
    }
    std::string title = "Test Window will close in ";
    GLFWwindow* window = glfwCreateWindow(800, 600, (title + "5s").c_str(), nullptr, nullptr);
    if (!window) {
        std::cout << "Test failed on window creation"  << std::endl;
        glfwTerminate();
        return false;
    }
    const auto start = std::chrono::steady_clock::now();
    while(!glfwWindowShouldClose(window)) {
        const std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
        const auto sec = duration.count();
        if (sec >= 5) {
            glfwSetWindowShouldClose(window, true);
        } else {
            glfwSetWindowTitle(window, (title + utos(5 - sec)).c_str());
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Tested successfully!" << std::endl;
    return true;
}