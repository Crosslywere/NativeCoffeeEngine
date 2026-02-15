package io.coffee_engine;

import io.coffee_engine.util.NativeLoader;

import java.awt.*;

public class CoffeeEngine {

    static {
        NativeLoader.loadLibrary("coffee");
    }

    static native boolean Test();

    static native boolean TestVulkan();

    public static void main(String... args) {
        try (Window window = Window.createWindow("Coffee Engine", new Dimension(800, 600))) {
            window.run();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        System.out.println("Native Coffee Engine ran!");
    }
}
