cmake_minimum_required(VERSION 3.20)
project(Hazel)

file(GLOB_RECURSE HAZEL_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
    "vendor/stb_image/*.h"
    "vendor/stb_image/*.cpp"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HAZEL_SOURCES})

add_library(Hazel STATIC ${HAZEL_SOURCES})

target_precompile_headers(Hazel PRIVATE src/hzpch.h)

target_link_directories(Hazel PRIVATE
    "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64/ImGui"
)

target_include_directories(Hazel PUBLIC
    src
    vendor/spdlog/include
    vendor/GLFW/include
    vendor/Glad/include
    vendor/imgui
    vendor/glm
    vendor/stb_image
)

target_link_libraries(Hazel PRIVATE
    glfw
    Glad
    ImGui
    opengl32
)

target_compile_definitions(Hazel PUBLIC
    HZ_PLATFORM_WINDOWS
)

target_compile_definitions(Hazel PRIVATE
    HZ_BUILD_DLL
    HZ_ENABLE_ASSERTS
    GLFW_INCLUDE_NONE
    $<$<CONFIG:Debug>:HZ_DEBUG>
    $<$<CONFIG:Release>:HZ_RELEASE>
    $<$<CONFIG:Dist>:HZ_DIST>
)

set_target_properties(Hazel PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64/Hazel"
)


target_compile_definitions(Hazel PRIVATE
    ASSET_PATH="${CMAKE_SOURCE_DIR}/Sandbox/assets"
)