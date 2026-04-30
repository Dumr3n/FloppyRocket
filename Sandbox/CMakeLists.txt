cmake_minimum_required(VERSION 3.20)
project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES
    "src/*.cpp"
    "src/*.h"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

add_executable(Sandbox ${SANDBOX_SOURCES})

target_include_directories(Sandbox PRIVATE
    ../Hazel/src
    ../Hazel/vendor/spdlog/include    
)

target_link_libraries(Sandbox PRIVATE Hazel)

target_compile_definitions(Sandbox PRIVATE
    HZ_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:HZ_DEBUG>
    $<$<CONFIG:Release>:HZ_RELEASE>
    $<$<CONFIG:Dist>:HZ_DIST>
)

set_target_properties(Sandbox PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64/Sandbox"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64/Sandbox"
)

target_compile_definitions(Sandbox PRIVATE
    ASSET_PATH="${CMAKE_SOURCE_DIR}/Sandbox/assets"
)