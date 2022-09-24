#ifndef AUTM_IMGUILAYER_H
#define AUTM_IMGUILAYER_H

#include "Core/Layer.h"

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();

    ~ImGuiLayer();

    void onInit() override;

    void onShutdown() override;

    void onEvent(Event& event) override;

protected:
    void begin(float ts);

    void end();
};


#endif //AUTM_IMGUILAYER_H
