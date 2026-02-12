package io.coffee_engine;

import io.coffee_engine.util.NativeLoader;

import java.awt.Dimension;
import java.io.Closeable;

public final class Window implements Closeable {

    static {
        NativeLoader.loadLibrary("coffee_window");
    }

    private static native Window nCreateWindow(String window, Dimension d);

    private static native void nRun(long handle);

    private final long handle;

    private Window(long handle) {
        this.handle = handle;
    }

    public static Window createWindow(String title, Dimension dimension) {
        return nCreateWindow(title, dimension);
    }

    public void run() {
        nRun(this.handle);
    }

    public native void close();

}
