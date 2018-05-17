#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include "Level.hpp"

namespace Zenon {

    class LevelSelectorState : public State {
    public:
        LevelSelectorState(GameDataRef l_data, bool rewardisOn, bool chargeGame);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        void RetrieveReward();
        void ChangeState();
        void ProcessRewards();
        void InitPanicLevelGUI();
        void CallGameOver();

    private:
        GameDataRef m_data;
        std::vector<Level*> m_levels;
        std::vector<sf::RectangleShape> m_panicLevels;
        std::vector<sf::RectangleShape> m_confidence;
        sf::Text m_moneyText;
        sf::Sprite m_background;
        sf::Sprite m_backButton;
        sf::Sprite m_moneyBackground;
        bool selected = false;
        bool m_charging;
    };
}