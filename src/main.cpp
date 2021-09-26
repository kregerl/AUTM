#include "App/Application.h"

int main() {
    auto *app = Application::createInstance();
    app->run();
    delete app;
    return 0;
}
