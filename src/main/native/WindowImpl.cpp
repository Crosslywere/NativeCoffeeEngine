#include <io_coffee_engine_Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static inline GLFWwindow *getWindowHandleFromInstance(JNIEnv *env, jobject inst)
{
    jclass clazz = env->FindClass("io/coffee_engine/Window");
    jfieldID field = env->GetFieldID(clazz, "handle", "J");
    jlong handle = env->GetLongField(inst, field);
    return reinterpret_cast<GLFWwindow *>(handle);
}

JNIEXPORT jobject JNICALL Java_io_coffee_1engine_Window_nCreateWindow(JNIEnv *env, jclass cls)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
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
    return env->NewObject(cls, constructor, reinterpret_cast<jlong>(window));
}

JNIEXPORT void JNICALL Java_io_coffee_1engine_Window_run(JNIEnv *env, jobject inst)
{
    GLFWwindow *window = getWindowHandleFromInstance(env, inst);
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
    glfwTerminate();
}