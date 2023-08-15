#include <Core/EntryPoint.h>
#include "Mandelbrot.h"
#include "DemoLayer.h"
#include "RayMarching.h"
#include "EntityLayer.h"

class App: public Application {
public:
    App() {
//        pushLayer(new Mandelbrot());
//        pushLayer(new RayMarching());
        push_layer(new EntityLayer());
        push_overlay(new DemoLayer());
    }

    ~App() {

    }
};

Application* create_application() {
    AUTM_DEBUG("Create App");
    return new App();
}