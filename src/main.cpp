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

