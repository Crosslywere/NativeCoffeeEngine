#include <io_coffee_engine_test_TestUtil.h>
#include <stdexcept>

class VulkanApp
{
public:
    void run()
    {
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan()
    {
    }

    void mainLoop()
    {
    }

    void cleanup()
    {
    }
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