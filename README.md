# Native Coffee Engine

This is a native implementation of the [Coffee Engine](https://github.com/Crosslywere/CoffeeEngine). 

The "Native" means it will no longer depend on [LWJGL](https://lwjgl.org) for OpenGL calls.
As I would be binding the calls through Java Native Interface(JNI).

## How to Build

```shell
# Generates the native
mvn clean compile
# Runs the cmake command
mvn exec:exec@cmake
# Runs the make command
mvn exec:exec@make
```

The shared library files are copied to the resource file after building.
