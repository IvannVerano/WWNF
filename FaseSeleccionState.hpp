#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "FichaTrampa.hpp"
#include "HUD.hpp"
#include <vector>

namespace Zenon {

    class FaseSeleccionState : public State {
    public:
        FaseSeleccionState(GameDataRef l_data);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        void ChangeState();
    private:
        GameDataRef m_data;
        std::vector<FichaTrampa *> m_trampasdisp;
        std::vector<FichaTrampa *> m_trampasSel;
        sf::Sprite m_boton;
        int m_dineroJugador;
    };
}