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

    void ImGuiWrapper::addParameter(FdrParameters::Parameter<float>& param) {
        float_params_.push_back(&param);
    }

    void ImGuiWrapper::addParameter(FdrParameters::Parameter<bool>& param) {
        bool_params_.push_back(&param);
    }

    void ImGuiWrapper::drawAllParameters() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        
        for (auto* param : float_params_) {
            float value = param->get();
            const char* name = param->name().c_str();
            if (ImGui::InputFloat(name, &value)) {
                param->set_and_renew(value);
            }
        }

        for (auto* param : bool_params_) {
            bool value = param->get();
            const char* name = param->name().c_str();
            if (ImGui::Checkbox(name, &value)) {
                param->set_and_renew(value);
            }
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}