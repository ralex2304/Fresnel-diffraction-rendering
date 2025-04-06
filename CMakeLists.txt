cmake_minimum_required(VERSION 3.16)

project(Fresnel-diffraction-rendering LANGUAGES CXX C)

set(ASSETS_DIR ${PROJECT_SOURCE_DIR}/assets)
set(ASSETS_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/assets)

file(RELATIVE_PATH
    ASSETS_LOCATION
    ${CMAKE_INSTALL_PREFIX}/bin
    ${ASSETS_INSTALL_DIR}
)

include(cmake/tools.cmake)

include(cmake/defaults.cmake)

include(cmake/third_party.cmake)


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_PATH="${ASSETS_LOCATION}")

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE fdr-defaults glad glfw ImGui OpenGL-shader-lib::OpenGL-shader-lib)

