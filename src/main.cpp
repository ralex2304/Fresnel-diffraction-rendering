#include <cassert>
#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#define GL_SILENCE_DEPRECATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <OpenGL-shader-lib/OpenGL-shader-lib.hpp>
#include "../FdrParameters.hpp"

using namespace OpenGLShaderLib;

class ShaderController : public FdrParameters::ParameterRenewer {
    private:
        OpenGLShaderLib::Shader& shader;
    public:
        ShaderController(OpenGLShaderLib::Shader& shader) : shader(shader) {}
    
        void renew(const std::string& name, bool value) const noexcept override {
            shader.use();
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            GLint loc = glGetUniformLocation(program, name.c_str());
            if (loc != -1) glUniform1i(loc, value);
        }
    
        void renew(const std::string& name, int value) const noexcept override {
            shader.use();
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            GLint loc = glGetUniformLocation(program, name.c_str());
            if (loc != -1) glUniform1i(loc, value);
        }
    
        void renew(const std::string& name, float value) const noexcept override {
            shader.use();
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            GLint loc = glGetUniformLocation(program, name.c_str());
            if (loc != -1) glUniform1f(loc, value);
        }
    
        void use() { shader.use(); }
    };

class DiffractionParams {
    public:
        FdrParameters::Parameter<float> slit_width;
        FdrParameters::Parameter<float> wavelength;
        FdrParameters::Parameter<float> distance;
        FdrParameters::Parameter<bool> showPattern;
        FdrParameters::Parameter<bool> showGrid;

        DiffractionParams(const FdrParameters::ParameterRenewer& renewer)
            : slit_width(renewer, "u_slit_width", 0.1f),
            wavelength(renewer, "u_wavelength", 550.0f),
            distance(renewer, "u_distance", 1000.0f),
            showPattern(renewer, "u_show_pattern", true),
            showGrid(renewer, "u_show_grid", false) {}
};

class UIRenderer {
    private:
        ImVec2 window_size;        
    public:
        UIRenderer() : window_size(500, 200) {}
        
        void render(DiffractionParams& params) {
            ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
            ImGui::Begin("Diffraction Controls", nullptr, 
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse
            );
            
            bool showPattern = params.showPattern.get();
            if (ImGui::Checkbox("Show pattern", &showPattern)) {
                params.showPattern.set_and_renew(showPattern);
            }
            
            bool showGrid = params.showGrid.get();
            if (ImGui::Checkbox("Show grid", &showGrid)) {
                params.showGrid.set_and_renew(showGrid);
            }
            
            ImGui::Separator();
            ImGui::Text("Slit Parameters:");
            
            float slit_width = params.slit_width.get();
            if (ImGui::InputFloat("Slit width (mm)", &slit_width, 0.01f, 0.1f, "%.3f")) {
                params.slit_width.set_and_renew(slit_width);
            }
            
            float wavelength = params.wavelength.get();
            if (ImGui::InputFloat("Wavelength (nm)", &wavelength, 1.0f, 10.0f, "%.1f")) {
                params.wavelength.set_and_renew(wavelength);
            }
            
            float distance = params.distance.get();
            if (ImGui::InputFloat("Distance (mm)", &distance, 10.0f, 100.0f, "%.0f")) {
                params.distance.set_and_renew(distance);
            }
            
            ImGui::End();
        }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

const unsigned int SCREEN_WIDTH  = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Fresnel diffraction", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Shader shader(ASSETS_PATH"/shaders/test.vs", ASSETS_PATH"/shaders/test.fs");
    ShaderController shaderController(shader);
    DiffractionParams params(shaderController);

    constexpr float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    constexpr unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    UIRenderer uiRenderer;

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        uiRenderer.render(params);

        process_input(window);

        glClearColor(0.0, 0.0, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderController.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window) {
    assert(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    assert(window);
    glViewport(0, 0, width, height);
}