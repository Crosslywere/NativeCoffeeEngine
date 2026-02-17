#include <io_coffee_engine_test_TestUtil.h>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#define TOTAL_RUNTIME 5.0

class VulkanApp
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(800, 600, "Testing Vulkan (5s)", nullptr, nullptr);
    }

    void initVulkan()
    {
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            if (glfwGetTime() >= TOTAL_RUNTIME)
            {
                glfwSetWindowShouldClose(window, true);
            }
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
};

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_test_TestUtil_TestVulkan(JNIEnv *env, jclass)
{
    VulkanApp app;
    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what());
        return false;
    }
    return true;
}