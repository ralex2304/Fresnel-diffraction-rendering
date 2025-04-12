#include "FdrWindow/FdrGLFW/FdrGLFW.hpp"
#include "FdrWindow/FdrWindow.hpp"

using namespace FdrWindow;

int main() {
    constexpr unsigned int kScreenWidth  = 800;
    constexpr unsigned int kScreenHeight = 800;

    constexpr FdrGLFW::opengl_version_t kOpenglVersion = {.context_version_major = 3,
                                                          .context_version_minor = 3};

    Window window(kScreenWidth, kScreenHeight, "Fresnel diffraction", kOpenglVersion,
                  ASSETS_PATH"/shaders/fdr.vs", ASSETS_PATH"/shaders/fdr.fs");

    while (!window.should_close()) {
        window.process();
    }

    return 0;
}

