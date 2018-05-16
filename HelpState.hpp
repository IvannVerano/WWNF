#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"


namespace Zenon{
    class HelpState:public State {
    public:
        HelpState(GameDataRef l_data);
        ~HelpState();
        void Init();
        void HandleInput();
        void NewGame();
        void Update(float dt);
        void Draw(float dt);
        void Return();
    private:
        GameDataRef m_data;
        sf::Sprite m_HelpBG;
        sf::Sprite m_HelpReturn;
    };
}



