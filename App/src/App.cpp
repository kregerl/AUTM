#include <Core/EntryPoint.h>
#include "Mandelbrot.h"
#include "DemoLayer.h"
#include "RayMarching.h"
#include "EntityLayer.h"
#include "CustomShader.h"

class App : public Application {
public:
    App() {
//        push_layer(new Mandelbrot());
//        push_layer(new RayMarching());
//        push_layer(new EntityLayer());
        push_layer(new CustomShader());
//        push_overlay(new DemoLayer());
    }

    ~App() {

    }
};

Application* create_application() {
    AUTM_DEBUG("Create App");
    return new App();
}