#include <Core/EntryPoint.h>
#include "Mandelbrot.h"

class App: public Application {
public:
    App() {
        pushLayer(new Mandelbrot());
    }

    ~App() {

    }
};

Application* createApplication() {
    AUTM_DEBUG("Create App");
    return new App();
}