#ifndef AUTM_DEMOLAYER_H
#define AUTM_DEMOLAYER_H

#include <Scene/Scene.h>
#include "Imgui/ImGuiLayer.h"

class DemoLayer : public ImGuiLayer {
public:
    DemoLayer() = default;

    void on_update(float ts) override;
};


#endif //AUTM_DEMOLAYER_H
