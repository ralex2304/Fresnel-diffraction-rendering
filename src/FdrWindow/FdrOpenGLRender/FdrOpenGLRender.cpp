#include <filesystem>
#include <glad/gl.h>
#include <OpenGL-shader-lib/OpenGL-shader-lib.hpp>

#include "FdrWindow/FdrOpenGLRender/FdrOpenGLRender.hpp"

namespace FdrOpenGLRender {

OpenGLRender::OpenGLRender(const std::filesystem::path& vshader_path,
                           const std::filesystem::path& fshader_path)
    : shader_(vshader_path, fshader_path) {

    shader_.use();

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices_), kVertices_, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices_), kIndices_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

OpenGLRender::~OpenGLRender() {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}

void OpenGLRender::render() const noexcept {
    shader_.use();
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, sizeof(kIndices_) / sizeof(*kIndices_), GL_UNSIGNED_INT, 0);
}

}; //< namespace FdrOpenGLRender

