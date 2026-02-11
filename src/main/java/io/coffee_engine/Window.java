package io.coffee_engine;

import io.coffee_engine.util.NativeLoader;

import java.io.Closeable;

public final class Window implements Closeable {

    static {
        NativeLoader.loadLibrary("coffee_window");
    }

    private static native Window nCreateWindow();

    private final long handle;

    private Window(long handle) {
        this.handle = handle;
    }

    public static Window createWindow() {
        return nCreateWindow();
    }

    public native void run();

    public native void close();

}
