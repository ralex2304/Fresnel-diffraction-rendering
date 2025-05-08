#include "FdrWindow/FdrImGui/FdrImGui.hpp"
#include "FdrWindow/FdrParameters/FdrParameters.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <unordered_map>

namespace FdrImGui {

ImGuiWrapper::ImGuiWrapper(GLFWwindow* glfw_window, FdrParameters::ParametersStorage& params)
    : params_(params) {

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

void ImGuiWrapper::process() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");

    draw_parameters(params_.storage<float>());
    draw_parameters(params_.storage<int>());
    draw_parameters(params_.storage<bool>());

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

template <typename T>
void ImGuiWrapper::draw_parameters(std::unordered_map<std::string, Params::Parameter<T>>& params) {
    for (auto& iter: params) {
        FdrParameters::Parameter<T>& param = iter.second;
        T value = param.get();
        if (input_wrapper_(param.label.c_str(), &value)) {
            param.set(value);
        }
    }
}

bool ImGuiWrapper::input_wrapper_(const char* label, float* value) {
    return ImGui::InputFloat(label, value);
}

bool ImGuiWrapper::input_wrapper_(const char* label, int* value) {
    return ImGui::InputInt(label, value);
}

bool ImGuiWrapper::input_wrapper_(const char* label, bool* value) {
    return ImGui::Checkbox(label, value);
}

}; //< namespace FdrImGui

