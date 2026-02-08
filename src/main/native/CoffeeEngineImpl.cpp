#include "io_coffee_engine_CoffeeEngine.h"
#include <iostream>

using std::cout;
using std::endl;

JNIEXPORT jboolean JNICALL Java_io_coffee_1engine_CoffeeEngine_Test(JNIEnv *env, jclass clazz)
{
    cout << "Tested successfully!" << endl;
    return true;
}