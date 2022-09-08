#include <Core/Log.h>
#include "App/Application.h"

int main() {
    Log::init();
    auto* app = Application::createInstance();
    app->run();
    delete app;
    return 0;
}
