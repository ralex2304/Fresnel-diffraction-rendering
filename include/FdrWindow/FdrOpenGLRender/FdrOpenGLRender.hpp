#pragma once

#include <stdexcept>
#include <OpenGL-shader-lib/OpenGL-shader-lib.hpp>
#include <filesystem>

namespace FdrOpenGLRender {
    using namespace OpenGLShaderLib;

    class OpenGLRender {
    public:
        OpenGLRender(const std::filesystem::path& vshader_path,
                     const std::filesystem::path& fshader_path);

        ~OpenGLRender() noexcept;

        void render() noexcept;

    private:
        Shader shader_;

        unsigned int VBO_ = 0;
        unsigned int VAO_ = 0;
        unsigned int EBO_ = 0;

        static constexpr float VERTICES_[] = {
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
        };

        static constexpr unsigned int INDICES_[] = {
            0, 1, 3,
            1, 2, 3,
        };
    };
};
