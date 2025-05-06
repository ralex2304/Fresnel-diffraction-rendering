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
          imgui_(glfw_.getWindow())  
    {
        parameters_storage_.add(wavelength_param_);
        parameters_storage_.add(hole_radius_param_);
        parameters_storage_.add(screen_distance_param_);
        parameters_storage_.add(show_grid_param_);
    }

    void process() noexcept {
        opengl_.render();
        imgui_.drawParameters(parameters_storage_); // Изменено
        glfw_.process();
    }

    bool should_close() const noexcept { return glfw_.should_close(); }

private:
    GLFW::GLFW             glfw_;
    GLR::OpenGLRender      opengl_;
    FdrImGui::ImGuiWrapper imgui_; 

    FdrParameters::ParametersStorage parameters_storage_;

    FdrParameters::Parameter<float> wavelength_param_{
        opengl_, "u_wavelength", "Wavelength (nm)", 500.0f
    };
    FdrParameters::Parameter<float> hole_radius_param_{
        opengl_, "u_hole_radius", "Hole radius (mm)", 5.0f
    };
    FdrParameters::Parameter<float> screen_distance_param_{
        opengl_, "u_screen_distance", "Screen distance (mm)", 50.0f
    };    // Параметры теперь создаются с display name:
    FdrParameters::Parameter<bool> show_grid_param_{
        opengl_, "u_show_grid", "Show grid", false
    };
};
} // namespace FdrWindow

