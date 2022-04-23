cmake_minimum_required(VERSION 3.21)

# ---- Project ----

project(
        gibby
        VERSION 0.1.0
        LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
            FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME imgui
        VERSION 1.87
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG 1ee252772ae9c0a971d06257bb5c89f628fa696a
        DOWNLOAD_ONLY YES
)
if(imgui_ADDED)
    file(GLOB imgui_SOURCES ${imgui_SOURCE_DIR}/*.cpp)

    if (WIN32)
        file(GLOB imgui_BACKEND_SOURCES ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp)
    endif ()

    add_library(imgui ${imgui_SOURCES} ${imgui_BACKEND_SOURCES})
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

    if (WIN32)
        if (CMAKE_SIZEOF_VOID_P EQUAL 4)
            target_compile_definitions(imgui PUBLIC ImTextureID=ImU64)
        endif ()
    endif ()
endif ()

# ---- Create executable ----

if (WIN32)
    set(PLATFORM_SOURCES src/platform/render/win32_dx11.cpp src/platform/render/win32_dx11.h)
endif ()
add_executable(${PROJECT_NAME} ${PLATFORM_SOURCES} src/main.cpp src/core/Application.cpp src/core/Application.h src/platform/render.cpp src/platform/render.h src/sys/Processor.cpp src/sys/Processor.h src/sys/registers.h src/sys/Memory.cpp src/sys/Memory.h src/sys/CPU.cpp src/sys/CPU.h src/sys/Graphics.cpp src/sys/Graphics.h src/sys/Audio.cpp src/sys/Audio.h)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)

# Link dependencies
if (WIN32)
    set(PLATFORM_LINK_LIBRARIES d3d11.lib)
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LINK_LIBRARIES} imgui)