#ifndef AUTM_IMGUILAYER_H
#define AUTM_IMGUILAYER_H

#include "Core/Layer.h"

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();

    ~ImGuiLayer() override;

    void on_init() override;

    void on_shutdown() override;

    void on_event(Event& event) override;

    void begin(float ts);

    void end();
};


#endif //AUTM_IMGUILAYER_H
