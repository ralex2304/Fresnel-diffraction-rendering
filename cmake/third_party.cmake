include(cmake/CPM.cmake)

CPMAddPackage(
  NAME glfw
  VERSION 3.3.10
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.10
  OPTIONS "BUILD_SHARED_LIBS ON"
          "GLFW_BUILD_EXAMPLES OFF"
          "GLFW_BUILD_TESTS OFF"
          "GLFW_BUILD_DOCS OFF"
)

CPMAddPackage(
    NAME OpenGL-shader-lib
    GITHUB_REPOSITORY ralex2304/OpenGL-shader-lib
    VERSION 1.0.1
)

CPMAddPackage(
    NAME ImGui
    GITHUB_REPOSITORY ocornut/imgui
    VERSION 1.91.9b
    DOWNLOAD_ONLY YES
)

if (ImGui_ADDED)
    file(GLOB ImGui_SOURCES ${ImGui_SOURCE_DIR}/*.cpp)

    add_library(ImGui STATIC
        ${ImGui_SOURCES}
        ${ImGui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${ImGui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_link_libraries(ImGui PUBLIC glfw)

    target_include_directories(ImGui PUBLIC ${ImGui_SOURCE_DIR})

    target_compile_definitions(ImGui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
endif ()
