cmake_minimum_required(VERSION 3.28)
project(NativeCoffeeEngine LANGUAGES C CXX)
find_package(JNI REQUIRED)
set(NATIVE_DIR "${CMAKE_SOURCE_DIR}/src/main/native")
add_subdirectory(src/main/native/vendor/glfw)
include_directories(
    ${JNI_INCLUDE_DIRS}
    ${NATIVE_DIR}
    "${NATIVE_DIR}/vendor/glad/include"
)
file(GLOB NATIVE_FILES "${NATIVE_DIR}/*.cpp")
# FOR Testing
add_library(coffee SHARED
    ${NATIVE_FILES}
    "${NATIVE_DIR}/vendor/glad/src/glad.c"
)
target_link_libraries(coffee glfw)
# Window Management
add_library(coffee_window SHARED
    "${NATIVE_DIR}/WindowImpl.cpp"
    "${NATIVE_DIR}/vendor/glad/src/glad.c"
)
target_link_libraries(coffee_window glfw)
# Post build copy
get_target_property(LIB_OUTPUT coffee ARCHIVE_OUTPUT_DIRECTORY)
set(NATIVE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/src/main/resources/native")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/macos")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()
add_custom_target(copy_libs ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:coffee>
        $<TARGET_FILE:coffee_window>
        ${DESTINATION_DIR}
)