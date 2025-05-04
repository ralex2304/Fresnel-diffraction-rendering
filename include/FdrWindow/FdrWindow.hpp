#pragma once

#include <filesystem>
#include <string>

#include "FdrGLFW/FdrGLFW.hpp"
#include "FdrOpenGLRender/FdrOpenGLRender.hpp"
#include "FdrImGui/FdrImGui.hpp" 

namespace FdrWindow {
    namespace GLFW = FdrGLFW; 
    namespace GLR  = FdrOpenGLRender; 

    class Window {
    public:
        Window(int width, int height, const std::string& title,
               const GLFW::opengl_version_t& opengl_version,
               const std::filesystem::path& vshader_path,
               const std::filesystem::path& fshader_path)
            : glfw_(width, height, title, opengl_version),
              opengl_(vshader_path, fshader_path),
              imgui_(glfw_.getWindow()), 
              wavelength_param_(opengl_, "u_wavelength", 500.0f),
              slit_radius_param_(opengl_, "u_slit_radius", 0.1f),
              screen_distance_param_(opengl_, "u_screen_distance", 10.0f),
              show_grid_param_(opengl_, "u_show_grid", true)
        {
            imgui_.addParameter(wavelength_param_);
            imgui_.addParameter(slit_radius_param_);
            imgui_.addParameter(screen_distance_param_);
            imgui_.addParameter(show_grid_param_);
        }

        void process() noexcept {
            opengl_.render();
            imgui_.drawAllParameters();
            glfw_.process();
        }

        bool should_close() const noexcept { return glfw_.should_close(); }

    private:
        GLFW::GLFW             glfw_;
        GLR::OpenGLRender      opengl_;
        FdrImGui::ImGuiWrapper imgui_; 

        FdrParameters::Parameter<float> wavelength_param_;
        FdrParameters::Parameter<float> slit_radius_param_;
        FdrParameters::Parameter<float> screen_distance_param_;
        FdrParameters::Parameter<bool> show_grid_param_;
    };
} // namespace FdrWindow

