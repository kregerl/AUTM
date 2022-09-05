#include <Core/Log.h>
#include "App/Application.h"

int main() {
    Log::init();
    int i = 1;

    AUTM_CORE_INFO("This is info {}", i);
#ifdef DEBUG
    AUTM_INFO("Exists");
#else
    AUTM_INFO("Does not exist");
#endif
    auto* app = Application::createInstance();
    AUTM_CORE_INFO("After application creation");
    app->run();
    delete app;
    return 0;
}
