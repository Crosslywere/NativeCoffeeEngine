package io.coffee_engine.test;

import io.coffee_engine.util.NativeLoader;

public class TestUtil {

    static {
        NativeLoader.loadLibrary("coffee_test");
    }

    public static native boolean TestOpenGL();

    public static native boolean TestVulkan();

}
