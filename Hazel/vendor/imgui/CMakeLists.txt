cmake_minimum_required(VERSION 3.20)
project(ImGui)

add_library(ImGui STATIC
    imconfig.h
    imgui.h
    imgui.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_demo.cpp
)

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ImGui PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-windows-x64/ImGui"
)


target_compile_options(ImGui PRIVATE
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Release>:/O2>
    $<$<CONFIG:Dist>:/O2>
)

target_compile_definitions(ImGui PRIVATE
    "IMGUI_API=__declspec(dllexport)"
    $<$<CONFIG:Debug>:HZ_DEBUG>
    $<$<CONFIG:Release>:HZ_RELEASE>
    $<$<CONFIG:Dist>:HZ_DIST>
)
