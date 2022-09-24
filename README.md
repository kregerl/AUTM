# Autm 

Autm is a basic 2d rendering engine with few layers of abstraction over OpenGL to make developing graphics programs easier. 

  
## Getting Started
Create a cmake file for your application and target the Autm library.
```cmake
target_link_libraries(${PROJECT_NAME} PUBLIC Autm)
```
Create your main application class:  
App.cpp
```c++
// App.cpp
#include <Core/EntryPoint.h>
#include "LayerName.h"

class App: public Application {
public:
    App() {
        pushLayer(new LayerName());
    }

    ~App() {

    }  
};

Application* createApplication() {
    return new App();
}
```
Create a layer to start rendering to the screen.  
```c++
// LayerName.h
#include <Core/Layer.h>
#include <Event/MouseEvents.h>
#include <Renderer/OrthographicCamera.h>

class LayerName : public Layer {

public:
    LayerName();

    virtual ~LayerName() = default;

    virtual void onInit() override;

    virtual void onShutdown() override;

    virtual void onUpdate(float ts) override;

    virtual void onEvent(Event& event) override;
private:
    OrthographicCamera m_camera;
```
```c++
// LayerName.cpp
#include "LayerName.h"

#include <Renderer/RenderSystem.h>
#include <Renderer/Renderer2D.h>
#include <Core/Log.h>

Mandelbrot::Mandelbrot() : Layer("Mandelbrot"), m_camera(-1.7777778, 1.7777778, 1, -1) {
}

void Mandelbrot::onInit() {
}

void Mandelbrot::onShutdown() {
}

void Mandelbrot::onUpdate(float ts) {

    RenderSystem::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Renderer2D::begin(m_camera);

    Renderer2D::drawQuad(glm::vec3(0.0f), glm::vec2(0.5f), 0.0f);

    Renderer2D::end();
}

void Mandelbrot::onEvent(Event& event) {
    // EventDispatcher dispatcher(event);
    // dispatcher.dispatchEvent<MouseButtonPressedEvent>(AUTM_BIND_EVENT(Mandelbrot::onMouseButtonPressed));
}
```
For more information please see the Examples(Doesn't exist yet) directory