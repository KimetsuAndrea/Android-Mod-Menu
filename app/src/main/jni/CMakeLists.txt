cmake_minimum_required(VERSION 3.22.1)

set(ANDROID_ARM_MODE arm)

project("MyLibName")

# Keystone static library
add_library(Keystone STATIC IMPORTED)
set_target_properties(Keystone PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/Deps/Keystone/libs-android/${ANDROID_ABI}/libkeystone.a)

# Dobby static library
add_library(Dobby STATIC IMPORTED)
set_target_properties(Dobby PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/Dobby/${ANDROID_ABI}/libdobby.a)

# Main shared library
add_library(MyLibName SHARED
        Main.cpp
        Menu/Jni.cpp
        Menu/Menu.cpp
        Menu/Setup.cpp
        Includes/Utils.cpp
        KittyMemory/KittyAsm.cpp
        KittyMemory/KittyIOFile.cpp
        KittyMemory/KittyMemory.cpp
        KittyMemory/KittyPtrValidator.cpp
        KittyMemory/KittyScanner.cpp
        KittyMemory/KittyUtils.cpp
        KittyMemory/MemoryBackup.cpp
        KittyMemory/MemoryPatch.cpp
        xDL/xdl.c
        xDL/xdl_iterate.c
        xDL/xdl_linker.c
        xDL/xdl_lzma.c
        xDL/xdl_util.c
)

# Compiler flags
target_compile_options(MyLibName PRIVATE
        -w -Wno-error=format-security -fvisibility=default -fpermissive -fexceptions -Werror
        -Wno-error=c++11-narrowing -Wall
)

# C++ standard
set_target_properties(MyLibName PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

# Linker flags
set_target_properties(MyLibName PROPERTIES
        LINK_FLAGS "-Wl,--gc-sections,--strip-all"
)

# Include directories
target_include_directories(MyLibName PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/
        ${CMAKE_CURRENT_SOURCE_DIR}/Dobby/
)

# Libraries to link
target_link_libraries(MyLibName
        Keystone
        Dobby
        log
        android
        EGL
        GLESv2
)
