#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Trampa.hpp"
#include "Placer.hpp"
#include <vector>

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
        int trampa;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;
        std::vector<SplashState*> states;
        std::vector<Trampa*> trampas;
        std::vector<Placer*> placer;
    };
}