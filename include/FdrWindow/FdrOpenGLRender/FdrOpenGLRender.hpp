#pragma once

#include <OpenGL-shader-lib/OpenGL-shader-lib.hpp>
#include <filesystem>

#include "FdrWindow/FdrParameters/FdrParameters.hpp"

namespace FdrOpenGLRender {

class OpenGLRender: public FdrParameters::ParameterRenewer {
public:
    OpenGLRender(const std::filesystem::path& vshader_path,
                 const std::filesystem::path& fshader_path);

    ~OpenGLRender();

    void render() const noexcept;

    virtual void renew(const std::string& name, const bool value) const noexcept override {
        shader_.use();
        shader_.set_bool(name, value);
    };

    virtual void renew(const std::string& name, const int value) const noexcept override {
        shader_.use();
        shader_.set_int(name, value);
    };

    virtual void renew(const std::string& name, const float value) const noexcept override {
        shader_.use();
        shader_.set_float(name, value);
    };

private:
    OpenGLShaderLib::Shader shader_;

    unsigned int VBO_ = 0;
    unsigned int VAO_ = 0;
    unsigned int EBO_ = 0;

    static constexpr float kVertices_[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
    };

    static constexpr unsigned int kIndices_[] = {
        0, 1, 3,
        1, 2, 3,
    };
};

}; //< namespace FdrOpenGLRender

