#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include "Level.hpp"

namespace Zenon {

    class LevelSelectorState : public State {
    public:
        LevelSelectorState(GameDataRef l_data, bool rewardisOn);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        void RetrieveReward();
        void ChangeState(sf::Vector2f l_coordinates);
        void ProcessRewards();
        void InitPanicLevelGUI();
        void CallGameOver();

    private:
        GameDataRef m_data;
        std::vector<Level*> m_levels;
        std::vector<sf::RectangleShape> m_panicLevels;
        std::vector<sf::Text> m_levelNames;
        sf::Text m_moneyText;
        sf::Sprite m_background;
        bool selected = false;
    };
}