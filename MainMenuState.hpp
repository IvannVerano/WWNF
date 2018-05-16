#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "LevelSelectorState.hpp"
#include "HelpState.hpp"


namespace Zenon
{
    class MainMenuState: public State
    {
        public:
            MainMenuState(GameDataRef l_data);
            void Init();
            void HandleInput();
            void NewGame();
            void NewHelpState();
            void ChargeGame();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef m_data;
            sf::Sprite m_PlayButton;
            sf::Sprite m_Background;
            sf::Sprite m_ExitButton;
            sf::Sprite m_HelpButton;
            sf::Sprite m_ChargeButton;
            sf::Music mainTheme;
            
    };
}
