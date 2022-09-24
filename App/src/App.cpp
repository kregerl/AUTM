#include <Core/EntryPoint.h>
#include "Mandelbrot.h"
#include "DemoLayer.h"

class App: public Application {
public:
    App() {
        pushLayer(new Mandelbrot());
        pushOverlay(new DemoLayer());
    }

    ~App() {

    }
};

Application* createApplication() {
    AUTM_DEBUG("Create App");
    return new App();
}