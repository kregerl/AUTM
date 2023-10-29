#ifndef AUTM_GAMEOFLIFE_H
#define AUTM_GAMEOFLIFE_H


#include <Autm.h>
#include "../Simulation.h"

class GameOfLife : public Simulation {
public:
    GameOfLife();

    ~GameOfLife() = default;

    const std::shared_ptr<Shader>& simulate() override;

    void on_imgui_render() override;

//    glm::vec4 color_tint() const {
//        return {m_color_tint[0], m_color_tint[2], m_color_tint[2], 1.0f};
//    }

private:
//    float m_color_tint[3] = {1.0f, 1.0f, 1.0f};
    float m_board_size = 50.0f;

    std::shared_ptr<Shader> m_shader;
};


#endif //AUTM_GAMEOFLIFE_H
