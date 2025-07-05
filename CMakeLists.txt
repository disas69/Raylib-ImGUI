cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Raylib-ImGUI)
project(${PROJECT_NAME})

include(FetchContent)

# Fetch ImGui v1.91.8
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.8
)
FetchContent_MakeAvailable(imgui)

# ImGui static library
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})

set(RAYLIB_PATH ${PROJECT_SOURCE_DIR}/raylib)
include_directories(${RAYLIB_PATH}/include include)

set(RL_IMGUI_PATH ${PROJECT_SOURCE_DIR}/rlImGui)
include_directories(${RL_IMGUI_PATH}/include include)

set(TINY_FD_PATH ${PROJECT_SOURCE_DIR}/tinyfiledialogs)
include_directories(${TINY_FD_PATH}/include)

add_executable(${PROJECT_NAME} src/main.cpp
        ${RL_IMGUI_PATH}/src/rlImGui.cpp
        ${TINY_FD_PATH}/src/tinyfiledialogs.c
)

if (WIN32)
    link_directories(${RAYLIB_PATH}/lib/win)

    if (MSVC)
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/win/raylib.lib)
    else ()
        target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/win/libraylib.a)
    endif ()

    target_link_libraries(${PROJECT_NAME} imgui opengl32 gdi32 winmm)
elseif (APPLE)
    link_directories(${RAYLIB_PATH}/lib/macos)
    target_link_libraries(${PROJECT_NAME} ${RAYLIB_PATH}/lib/macos/libraylib.a)

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)

    target_link_libraries(${PROJECT_NAME}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
            "-framework OpenGL"
            imgui
    )
endif ()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)