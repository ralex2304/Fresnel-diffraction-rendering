#pragma once

#include <filesystem>
#include <string>

#include "FdrGLFW/FdrGLFW.hpp"
#include "FdrOpenGLRender/FdrOpenGLRender.hpp"

namespace FdrWindow {

namespace GLFW = FdrGLFW;
namespace GLR  = FdrOpenGLRender;

class Window {
public:
    Window(int width, int height, const std::string& title,
            const GLFW::opengl_version_t& opengl_version,
            const std::filesystem::path& vshader_path,
            const std::filesystem::path& fshader_path)
        : glfw_(width, height, title, opengl_version)
        , opengl_(vshader_path, fshader_path) {}

    void process() const noexcept {
        opengl_.render();
        glfw_.process();
    }

    bool should_close() const noexcept { return glfw_.should_close(); }

private:
    GLFW::GLFW glfw_;
    GLR::OpenGLRender opengl_;
};

}; //< namespace FdrWindow

