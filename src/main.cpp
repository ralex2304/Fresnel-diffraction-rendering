#include <cassert>

#include "FdrWindow/FdrGLFW/FdrGLFW.hpp"
#include "FdrWindow/FdrWindow.hpp"

using namespace FdrWindow;

const unsigned int SCREEN_WIDTH  = 800;
const unsigned int SCREEN_HEIGHT = 800;

int main() {

    constexpr opengl_version_t OPENGL_VERSION = {.context_version_major = 3,
                                                 .context_version_minor = 3};

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Fresnel diffraction", OPENGL_VERSION,
                  ASSETS_PATH"/shaders/fdr.vs", ASSETS_PATH"/shaders/fdr.fs");

    while (!window.should_close()) {
        window.process();
    }

    return 0;
}
/*
{
    // GLFW

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // OPENGL

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // OPENGL render

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

*/
