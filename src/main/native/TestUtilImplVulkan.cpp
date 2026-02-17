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
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize glfw");
        }
        if (!glfwVulkanSupported())
        {
            throw std::runtime_error("No vulkan hardware support on this system!");
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(800, 600, "Testing Vulkan (5s)", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create window!");
        }
    }

    void initVulkan()
    {
        createInstance();
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Native Coffee Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Native Coffee Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create vulkan instance");
        }
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
    VkInstance instance;
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