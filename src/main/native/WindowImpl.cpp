#include <io_coffee_engine_Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

struct Configuration
{
    int width;
    int height;
    const char *title;
};

static inline std::map<const jlong, GLFWwindow *> managed_windows;

static inline GLFWwindow *getWindowHandleFromInstance(JNIEnv *env, jobject inst)
{
    jclass clazz = env->FindClass("io/coffee_engine/Window");
    jfieldID field = env->GetFieldID(clazz, "handle", "J");
    jlong handle = env->GetLongField(inst, field);
    return managed_windows.at(handle);
}

static inline Configuration getConfiguration(JNIEnv *env, jstring title, jobject dimension)
{
    Configuration config;
    jclass dimensionClass = env->FindClass("java/awt/Dimension");

    jfieldID widthField = env->GetFieldID(dimensionClass, "width", "I");
    config.width = env->GetIntField(dimension, widthField);

    jfieldID heightField = env->GetFieldID(dimensionClass, "height", "I");
    config.height = env->GetIntField(dimension, heightField);

    config.title = env->GetStringUTFChars(title, nullptr);
    return config;
}

JNIEXPORT jobject JNICALL Java_io_coffee_1engine_Window_nCreateWindow(JNIEnv *env, jclass cls, jstring title, jobject dimension)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    auto config = getConfiguration(env, title, dimension);
    GLFWwindow *window = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        env->FatalError("Failed to create window!");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        env->FatalError("Failed to load OpenGL!");
    }
    jmethodID constructor = env->GetMethodID(cls, "<init>", "(J)V");
    const jlong handle = reinterpret_cast<jlong>(window);
    managed_windows.insert(std::make_pair(handle, window));
    return env->NewObject(cls, constructor, handle);
}

JNIEXPORT void JNICALL Java_io_coffee_1engine_Window_nRun(JNIEnv *env, jclass, jlong handle)
{
    GLFWwindow *window = managed_windows.at(handle);
    if (!window)
    {
        env->FatalError("Failed to get proper handle for run");
    }
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

JNIEXPORT void JNICALL Java_io_coffee_1engine_Window_close(JNIEnv *env, jobject inst)
{
    GLFWwindow *window = getWindowHandleFromInstance(env, inst);
    if (!window)
    {
        env->FatalError("Failed to get proper handle for close");
    }
    glfwDestroyWindow(window);
    managed_windows.erase(reinterpret_cast<jlong>(window));
    glfwTerminate();
}