#include <cassert>
#include <string>

#include "FdrWindow/FdrGLFW/FdrGLFW.hpp"

namespace FdrGLFW {

using namespace std::literals;

GLFW::GLFW(const int width, const int height, const std::string& title,
           const opengl_version_t& gl_version) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version.context_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version.context_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window_ == NULL) {
        glfwTerminate();
        throw glfw_failure("ERROR::WINDOW::GLFW_CREATE_WINDOW_ERROR");
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwTerminate();
        throw glfw_failure("ERROR::WINDOW::GLAD_INIT_FAILED");
    }

    assert(window_);
}

GLFW::~GLFW() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void GLFW::process() const noexcept {
    glfwPollEvents();
    process_keyboard();

    glfwSwapBuffers(window_);
}

bool GLFW::should_close() const noexcept {
    return glfwWindowShouldClose(window_);
}

void GLFW::process_keyboard() const noexcept {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_, true);
}

void GLFW::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept {
    assert(window);

    glViewport(0, 0, width, height);
}

}; //< namespace FdrGLFW

