#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Ataque.hpp"
#include "Enemigo.hpp"

namespace Zenon {

    class SplashState : public State {
    public:
        SplashState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Clock _clock;

        sf::Texture _backgroundTexture;
        sf::Sprite _background;
    
        Ataque * m_torreta;
        std::vector <Enemigo *> m_enemigos;
        
        sf::Clock m_clock_Spawn;
    };
}