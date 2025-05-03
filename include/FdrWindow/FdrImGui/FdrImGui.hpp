#pragma once

#include "FdrWindow/FdrParameters/FdrParameters.hpp"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <unordered_map>

namespace FdrImGui {
    class ImGuiWrapper : public FdrParameters::ParameterRenewer {
        public:
            ImGuiWrapper(GLFWwindow* glfw_window);
            ~ImGuiWrapper();

            void renew(const std::string& name, bool value)  const noexcept override;
            void renew(const std::string& name, int value)   const noexcept override;
            void renew(const std::string& name, float value) const noexcept override;

            template <typename T>
            void addParameter(const std::string& name, T& value);

            void drawAllParameters();
    
        private:
            mutable std::unordered_map<std::string, float*> float_params_;
            mutable std::unordered_map<std::string,  bool*>  bool_params_;
        };
} // namespace FdrImGui