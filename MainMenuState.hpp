#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "LevelSelectorState.hpp"


namespace Zenon
{
    class MainMenuState: public State
    {
        public:
            MainMenuState(GameDataRef l_data);
            void Init();
            void HandleInput();
            void NewGame();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef m_data;
            sf::Sprite m_PlayButton;
            sf::Sprite m_Background;
    };
}
