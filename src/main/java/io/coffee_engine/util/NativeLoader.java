package io.coffee_engine.util;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

/**
 * Custom native loader that loads the shared library from the resource folder packaged into the project
 * @author ChatGPT
 */
public class NativeLoader {
    public static void loadLibrary(String libName) {
        try {
            String os = System.getProperty("os.name").toLowerCase();
            String platform;
            if (os.contains("win")) {
                platform = "windows";
                libName += ".dll";
            }
            else if (os.contains("mac")) {
                platform = "macos";
                libName = "lib" + libName + ".dylib";
            }
            else {
                platform = "linux";
                libName = "lib" + libName + ".so";
            }
            String resourcePath = "/native/" + platform + "/" + libName;

            try (InputStream in = NativeLoader.class.getResourceAsStream(resourcePath)) {
                if (in == null) {
                    throw new RuntimeException("Native library not found: " + resourcePath);
                }

                Path temp = Files.createTempFile("jni-", libName);
                temp.toFile().deleteOnExit();

                Files.copy(in, temp, StandardCopyOption.REPLACE_EXISTING);
                System.load(temp.toAbsolutePath().toString());
            }
        } catch (Exception e) {
            throw new RuntimeException("Failed to load native library", e);
        }
    }
}
