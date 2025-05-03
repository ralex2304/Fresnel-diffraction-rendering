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
              imgui_(glfw_.getWindow()) {
                imgui_.addParameter("wavelength (nm)",              wavelength_);
                imgui_.addParameter("hole radius (mm)",            slit_radius_);
                imgui_.addParameter("distance to screen (mm)", screen_distance_);
                imgui_.addParameter("show grid",                     show_grid_);
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

        float wavelength_      = 500.0f;
        float slit_radius_     = 0.1f;
        float screen_distance_ = 1.0f;

        bool show_grid_        = true;
    };
} // namespace FdrWindow

