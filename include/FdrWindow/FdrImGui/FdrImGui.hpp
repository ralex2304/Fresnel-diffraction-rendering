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

        void addParameter(FdrParameters::Parameter<float>& param);
        void addParameter(FdrParameters::Parameter<bool>& param);

        void drawAllParameters();

    private:
    std::vector<FdrParameters::Parameter<float>*> float_params_;
    std::vector<FdrParameters::Parameter<bool>*> bool_params_;
    };
} // namespace FdrImGui