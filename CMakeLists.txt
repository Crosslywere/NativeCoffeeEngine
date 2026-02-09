cmake_minimum_required(VERSION 3.28)
project(NativeCoffeeEngine LANGUAGES C CXX)
find_package(JNI REQUIRED)
add_subdirectory(src/main/native/vendor/glfw)
include_directories(
    ${JNI_INCLUDE_DIRS}
    src/main/native
)
file(GLOB NATIVE_FILES src/main/native/*.cpp)
add_library(coffee SHARED ${NATIVE_FILES})
target_link_libraries(coffee glfw)
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
        ${DESTINATION_DIR}
)