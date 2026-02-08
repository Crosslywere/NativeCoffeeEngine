cmake_minimum_required(VERSION 3.28)
project(NativeCoffeeEngine LANGUAGES C CXX)
find_package(JNI REQUIRED)
include_directories(
    ${JNI_INCLUDE_DIRS}
    src/main/native
)
file(GLOB NATIVE_FILES src/main/native/*.cpp)
add_library(coffee SHARED ${NATIVE_FILES})
# Post build copy
get_target_property(LIB_OUTPUT coffee ARCHIVE_OUTPUT_DIRECTORY)
set(NATIVE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/src/main/resources/native")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OUTPUT "libcoffee.so")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OUTPUT "coffee.dll")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OUTPUT "libcoffee.dylib")
    set(DESTINATION_DIR "${NATIVE_OUTPUT_DIR}/macos")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()
add_custom_command(TARGET coffee POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${OUTPUT}" "${DESTINATION_DIR}/${OUTPUT}"
)