cmake_minimum_required(VERSION 3.28)
project(NativeCoffeeEngine LANGUAGES C CXX)
find_package(JNI REQUIRED)
find_package(Vulkan REQUIRED)
set(NATIVE_DIR "${CMAKE_SOURCE_DIR}/src/main/native")
add_subdirectory(src/main/native/vendor/glfw)
include_directories(
    ${JNI_INCLUDE_DIRS}
    ${Vulkan_INCLUDE_DIRS}
    ${NATIVE_DIR}
    "${NATIVE_DIR}/vendor/glad/include"
)
# Testing Utility
add_library(coffee_test SHARED
    "${NATIVE_DIR}/TestUtilImplOpenGL.cpp"
    "${NATIVE_DIR}/TestUtilImplVulkan.cpp"
    "${NATIVE_DIR}/vendor/glad/src/glad.c"
)
target_link_libraries(coffee_test glfw ${Vulkan_LIBRARIES})
# Window Management
add_library(coffee_window SHARED
    "${NATIVE_DIR}/WindowImpl.cpp"
    "${NATIVE_DIR}/vendor/glad/src/glad.c"
)
target_link_libraries(coffee_window glfw ${Vulkan_LIBRARIES})
# Post build copy
get_target_property(LIB_OUTPUT coffee_test ARCHIVE_OUTPUT_DIRECTORY)
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
add_custom_target(copy_to_resources ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:coffee_test>
        $<TARGET_FILE:coffee_window>
        ${DESTINATION_DIR}
)