#pragma once

#include <jni.h>
#include <string>
#include <sstream>

class JavaLogger
{
public:
    JavaLogger(JNIEnv *env)
        : env(env)
    {
        jclass systemClass = env->FindClass("java/lang/System");
        jclass outClass = env->FindClass("java/io/PrintStream");
        outObject = env->GetStaticObjectField(systemClass, env->GetStaticFieldID(systemClass, "out", "Ljava/io/PrintStream;"));
        printStrMethod = env->GetMethodID(outClass, "print", "(Ljava/lang/String;)V");
    }

    void print(const std::stringstream &stringstream) const
    {
        jstring utf = env->NewStringUTF(stringstream.str().c_str());
        env->CallVoidMethod(outObject, printStrMethod, utf);
    }

    void print(const std::string &message) const
    {
        jstring utf = env->NewStringUTF(message.c_str());
        env->CallVoidMethod(outObject, printStrMethod, utf);
    }

    void print(const char *message) const
    {
        jstring utf = env->NewStringUTF(message);
        env->CallVoidMethod(outObject, printStrMethod, utf);
    }

    const JavaLogger &operator<<(const char *string) const
    {
        this->print(string);
        return *this;
    }

    const JavaLogger &operator<<(const std::string &string) const
    {
        this->print(string);
        return *this;
    }

    const JavaLogger &operator<<(const std::stringstream &stringstream) const
    {
        this->print(stringstream);
        return *this;
    }

private:
    JNIEnv *env;
    jobject outObject;
    jmethodID printStrMethod;
};