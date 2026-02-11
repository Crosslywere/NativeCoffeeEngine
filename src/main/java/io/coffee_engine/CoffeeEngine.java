package io.coffee_engine;

import io.coffee_engine.util.NativeLoader;

public class CoffeeEngine {

    static {
        NativeLoader.loadLibrary("coffee");
    }

    static native boolean Test();

    public static void main(String... args) {
        try (Window window = Window.createWindow()) {
            window.run();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        System.out.println("Native Coffee Engine ran!");
    }
}
