#pragma once

#include <stdexcept>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace FdrGLFW {
    struct opengl_version_t {
        int context_version_major;
        int context_version_minor;
    };

    class GLFW {
    public:
        GLFW(int width, int height, const std::string& title,
             const opengl_version_t& gl_version);

        ~GLFW() noexcept;

        void process() const noexcept;

        bool should_close() const noexcept;

        class glfw_failure: public std::runtime_error {
            using std::runtime_error::runtime_error;
        };

    private:
        void process_keyboard() const noexcept;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;

    private:
        GLFWwindow* window_ = nullptr;
    };
};

