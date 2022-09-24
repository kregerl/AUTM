#ifndef AUTM_DEMOLAYER_H
#define AUTM_DEMOLAYER_H

#include "Imgui/ImGuiLayer.h"

class DemoLayer : public ImGuiLayer {
public:
    DemoLayer() = default;

    void onUpdate(float ts) override;
};


#endif //AUTM_DEMOLAYER_H
