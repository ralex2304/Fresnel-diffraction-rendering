#pragma once

#include "FdrWindow/FdrParameters/FdrParameters.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <unordered_map>

namespace FdrImGui {

namespace Params = FdrParameters;

class ImGuiWrapper {
    public:
    ImGuiWrapper(GLFWwindow* glfw_window, FdrParameters::ParametersStorage& params);
    ~ImGuiWrapper();

    void process();

private:
    FdrParameters::ParametersStorage& params_;

    template <typename T>
    void draw_parameters(std::unordered_map<std::string, Params::Parameter<T>>& params);

    bool input_wrapper_(const char* label, float* value);
    bool input_wrapper_(const char* label, int* value);
    bool input_wrapper_(const char* label, bool* value);
};

}; //< namespace FdrImGui

