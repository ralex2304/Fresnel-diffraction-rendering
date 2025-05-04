
add_library(FdrWindow STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/FdrParameters/FdrParameters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FdrOpenGLRender/FdrOpenGLRender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FdrGLFW/FdrGLFW.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FdrImGui/FdrImGui.cpp
)

target_include_directories(FdrWindow PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(FdrWindow PUBLIC fdr-defaults glad glfw OpenGL-shader-lib::OpenGL-shader-lib ImGui)

