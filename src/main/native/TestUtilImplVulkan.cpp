#include <io_coffee_engine_test_TestUtil.h>
#include <stdexcept>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#define TOTAL_RUNTIME 5.0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class VulkanApp
{
public:
    VulkanApp(JNIEnv *env) : env{env}
    {
        jclass systemClass = env->FindClass("java/lang/System");
        outObject = env->GetStaticObjectField(systemClass, env->GetStaticFieldID(systemClass, "out", "Ljava/io/PrintStream;"));
        printlnMethod = env->GetMethodID(env->FindClass("java/io/PrintStream"), "println", "(Ljava/lang/String;)V");
    }

    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void println(const std::string &message) const
    {
        jstring str = env->NewStringUTF(message.c_str());
        env->CallVoidMethod(outObject, printlnMethod, str);
    }

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
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Testing Vulkan (5s)", nullptr, nullptr);
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
        createInfo.enabledLayerCount = 0;
#if defined(__APPLE__)
        std::vector<const char *> requiredExtensions;
        for (uint32_t i = 0; i < glfwExtensionCount; i++)
        {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
#else
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
#endif

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create vulkan instance");
        }

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        println("Available extensions:");
        for (const auto &extension : extensions)
        {
            std::string message = "\t";
            message += extension.extensionName;
            println(message.c_str());
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
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

private:
    GLFWwindow *window;
    VkInstance instance;
    JNIEnv *env;
    jobject outObject;
    jmethodID printlnMethod;
};

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_test_TestUtil_TestVulkan(JNIEnv *env, jclass)
{
    VulkanApp app(env);
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