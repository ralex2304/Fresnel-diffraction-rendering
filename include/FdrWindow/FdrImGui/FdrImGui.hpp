#pragma once

#include "FdrWindow/FdrParameters/FdrParameters.hpp"

#include <vector>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <unordered_map>

namespace FdrImGui {
class ImGuiWrapper {
    public:
    ImGuiWrapper(GLFWwindow* glfw_window);
    ~ImGuiWrapper();

    void drawParameters(FdrParameters::ParametersStorage& storage);

private:
    void drawParameter(FdrParameters::Parameter<float>& param);
    void drawParameter(FdrParameters::Parameter<bool>& param);
};
} // namespace FdrImGui