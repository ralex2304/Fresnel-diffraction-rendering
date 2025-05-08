#pragma once

#include <filesystem>
#include <string>

#include "FdrGLFW/FdrGLFW.hpp"
#include "FdrOpenGLRender/FdrOpenGLRender.hpp"
#include "FdrWindow/FdrParameters/FdrParameters.hpp"
#include "FdrImGui/FdrImGui.hpp"

namespace FdrWindow {

namespace GLFW   = FdrGLFW;
namespace GLR    = FdrOpenGLRender;
namespace Params = FdrParameters;

class Window {
public:
    Window(int width, int height, const std::string& title,
           const GLFW::opengl_version_t& opengl_version,
           const std::filesystem::path& vshader_path,
           const std::filesystem::path& fshader_path)
        : glfw_(width, height, title, opengl_version)
        , opengl_(vshader_path, fshader_path)
        , imgui_(glfw_.get_window(), params_) {

        params_.add_parameter<float>(opengl_, "u_wavelength",  600.0f, "wavelength, nm");
        params_.add_parameter<float>(opengl_, "u_hole_radius", 0.2f,   "hole radius, mm");
        params_.add_parameter<float>(opengl_, "u_distance",    25.0f,  "distance to screen, mm");
        params_.add_parameter<bool> (opengl_, "u_show_grid",   false,  "show grid");
    }

    void process() noexcept {
        opengl_.render();
        imgui_.process();
        glfw_.process();
    }

    bool should_close() const noexcept { return glfw_.should_close(); }

private:
    GLFW::GLFW                  glfw_;
    GLR::OpenGLRender           opengl_;
    Params::ParametersStorage   params_;
    FdrImGui::ImGuiWrapper      imgui_;
};

} // namespace FdrWindow

