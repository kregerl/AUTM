#ifndef AUTM_ENTRYPOINT_H
#define AUTM_ENTRYPOINT_H

#include "Core/Log.h"
#include "App/Application.h"

extern Application* createApplication();

int main(int argc, char** argv) {
    Log::init();
    auto app = createApplication();
    app->run();
    delete app;
}

#endif //AUTM_ENTRYPOINT_H
