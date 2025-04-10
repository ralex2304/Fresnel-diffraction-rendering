#pragma once

#include <filesystem>
#include <string>

#include "FdrGLFW/FdrGLFW.hpp"
#include "FdrOpenGLRender/FdrOpenGLRender.hpp"

namespace FdrWindow {

    using namespace FdrGLFW;
    using namespace FdrOpenGLRender;

    class Window {
    public:
        Window(int width, int height, const std::string& title,
                const opengl_version_t& opengl_version,
                const std::filesystem::path& vshader_path,
                const std::filesystem::path& fshader_path):
            glfw_(width, height, title, opengl_version),
            opengl_(vshader_path, fshader_path) {}

        void process() noexcept {
            opengl_.render();
            glfw_.process();
        }

        bool should_close() noexcept { return glfw_.should_close(); }
    private:
        GLFW glfw_;
        OpenGLRender opengl_;
    };
};

