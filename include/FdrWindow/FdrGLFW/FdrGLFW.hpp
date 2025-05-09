#pragma once

#include <stdexcept>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace FdrGLFW {

class glfw_failure: public std::runtime_error {
        using std::runtime_error::runtime_error;
};

struct opengl_version_t {
    int context_version_major;
    int context_version_minor;
};

class GLFWWindowWrapper {
public:
    void create(const int width, const int height, const std::string& title);
    ~GLFWWindowWrapper();

    GLFWwindow* operator()() const {
        return window_;
    }
private:
    GLFWwindow* window_ = nullptr;
};

class GLFW {
public:
    GLFW(int width, int height, const std::string& title,
         const opengl_version_t& gl_version);
    ~GLFW();

    void process() const noexcept;

    bool should_close() const noexcept;

    GLFWwindow* get_window() const noexcept { return window_(); }

private:
    void process_keyboard() const noexcept;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;

private:
    GLFWWindowWrapper window_;
};

}; //< namespace FdrGLFW

