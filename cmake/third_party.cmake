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
    NAME glad
    GITHUB_REPOSITORY Dav1dde/glad
    GIT_TAG v2.0.8
    DOWNLOAD_ONLY YES
)

if (glad_ADDED)
    set(GLAD_GEN_DIR "${CMAKE_BINARY_DIR}/gladgen")
    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad STATIC REPRODUCIBLE QUIET LOCATION ${GLAD_GEN_DIR} LOADER API gl:core=3.3)
    include_directories("${GLAD_GEN_DIR}/include")
endif ()

CPMAddPackage(
    NAME OpenGL-shader-lib
    GITHUB_REPOSITORY ralex2304/OpenGL-shader-lib
    VERSION 1.0.0
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
