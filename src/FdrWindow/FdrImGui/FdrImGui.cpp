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

void ImGuiWrapper::drawParameters(FdrParameters::ParametersStorage& storage) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    
    for (auto it = storage.begin(); it != storage.end(); ++it) {
        (*it)->drawImGuiWidget();
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWrapper::drawParameter(FdrParameters::Parameter<float>& param) {
    float value = param.get();
    if (ImGui::InputFloat(param.display_name().c_str(), &value)) {
        param.set_and_renew(value);
    }
}
    
void ImGuiWrapper::drawParameter(FdrParameters::Parameter<bool>& param) {
    bool value = param.get();
    if (ImGui::Checkbox(param.display_name().c_str(), &value)) {
        param.set_and_renew(value);
    }
}

}