#include <cassert>
#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#define GL_SILENCE_DEPRECATION
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <OpenGL-shader-lib/OpenGL-shader-lib.hpp>

using namespace OpenGLShaderLib;

class DiffractionParams {
    private:
        float slit_width = 0.1f;  
        float wavelength = 550.0f;
        float distance   = 1000.0f;       
    public:
        void setSlitWidth(float width) { 
            slit_width = (width < 0.01f) ? 0.01f : (width > 2.0f) ? 2.0f : width; 
        }
        float getSlitWidth() const { return slit_width; }
        
        void setWavelength(float wave) { 
            wavelength = (wave < 380.0f) ? 380.0f : (wave > 780.0f) ? 780.0f : wave; 
        }
        float getWavelength() const { return wavelength; }
        
        void setDistance(float dist) { 
            distance = (dist < 100.0f) ? 100.0f : (dist > 5000.0f) ? 5000.0f : dist; 
        }
        float getDistance() const { return distance; }
        
        bool showPattern = true;  
        bool showGrid    = false;    
};

class ShaderController {
    private:
        OpenGLShaderLib::Shader& shader;        
    public:
        ShaderController(OpenGLShaderLib::Shader& shader) : shader(shader) {}
        
        void setUniform(const std::string& name, bool value) {
            shader.use();
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            GLint loc = glGetUniformLocation(program, name.c_str());
            if(loc != -1) {
                glUniform1i(loc, value ? 1 : 0);
            }
        }
        
        void setUniform(const std::string& name, float value) {
            shader.use();
            GLint program;
            glGetIntegerv(GL_CURRENT_PROGRAM, &program);
            GLint loc = glGetUniformLocation(program, name.c_str());
            if(loc != -1) {
                glUniform1f(loc, value);
            }
        }
        
        void use() { shader.use(); }
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
            
            ImGui::Checkbox("Show pattern", &params.showPattern);
            ImGui::Checkbox("Show grid", &params.showGrid);
            
            ImGui::Separator();
            ImGui::Text("Slit Parameters:");
            
            float slit_width = params.getSlitWidth();
            if(ImGui::InputFloat("Slit width (mm)", &slit_width, 0.01f, 0.1f, "%.3f")) {
                params.setSlitWidth(slit_width);
            }
            
            float wavelength = params.getWavelength();
            if(ImGui::InputFloat("Wavelength (nm)", &wavelength, 1.0f, 10.0f, "%.1f")) {
                params.setWavelength(wavelength);
            }
            
            float distance = params.getDistance();
            if(ImGui::InputFloat("Distance (mm)", &distance, 10.0f, 100.0f, "%.0f")) {
                params.setDistance(distance);
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
    if(window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGL(glfwGetProcAddress)) {
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

    DiffractionParams params;
    UIRenderer uiRenderer;

    while(!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        uiRenderer.render(params);

        process_input(window);

        glClearColor(0.0, 0.0, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderController.use();
        shaderController.setUniform("u_show_pattern", params.showPattern);
        shaderController.setUniform("u_show_grid",    params.showGrid);
        shaderController.setUniform("u_slit_width",   params.getSlitWidth());
        shaderController.setUniform("u_wavelength",   params.getWavelength());
        shaderController.setUniform("u_distance",     params.getDistance());

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