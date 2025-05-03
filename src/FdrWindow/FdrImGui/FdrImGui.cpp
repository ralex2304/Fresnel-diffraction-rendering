#include "FdrWindow/FdrImGui/FdrImGui.hpp"

namespace FdrImGui {
    ImGuiWrapper::ImGuiWrapper(GLFWwindow* glfw_window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    ImGuiWrapper::~ImGuiWrapper() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiWrapper::renew(const std::string& name, bool value) const noexcept {
        if (auto it = bool_params_.find(name); it != bool_params_.end()) {
            *it->second = value;
        }
    }

    void ImGuiWrapper::renew(const std::string& name, int value) const noexcept {}

    void ImGuiWrapper::renew(const std::string& name, float value) const noexcept {
        if (auto it = float_params_.find(name); it != float_params_.end()) {
            *it->second = value;
        }
    }

    template <typename T>
    void ImGuiWrapper::addParameter(const std::string& name, T& value) {
        if constexpr (std::is_same_v<T, float>) {
            float_params_[name] = &value;
        } else if constexpr (std::is_same_v<T, bool>) {
            bool_params_[name] = &value;
        }
    }

    void ImGuiWrapper::drawAllParameters() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        
        for (auto& [name, ptr] : float_params_) {
            ImGui::InputFloat(name.c_str(), ptr);
        }

        for (auto& [name, ptr] : bool_params_) {
            ImGui::Checkbox(name.c_str(), ptr);
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    template void ImGuiWrapper::addParameter<float>(const std::string&, float&);
    template void ImGuiWrapper::addParameter<bool> (const std::string&,  bool&);
}