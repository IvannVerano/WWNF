#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "SplashState.hpp"
#include "MathHelper.hpp"

namespace Zenon
{
    class PlaneReturnScene: public State
    {
        public:
            PlaneReturnScene(GameDataRef l_data, bool success);
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void StartGame();
            void SetPlaneRotation();
        private:
            GameDataRef m_data;
            sf::Sprite m_destiny;
            sf::Sprite m_nextButton;
            sf::Sprite m_plane;
            sf::Sprite m_background;
            sf::Sprite m_infobox;
            sf::Vector2f m_destinyPoint;
            sf::Vector2f m_trajectory;
            
            sf::Text m_textSuccess;
            sf::Text m_civilians;
            sf::Text m_trapUnlocked;
            sf::Text m_money;
            sf::Text m_confidenceReward;
            
            bool hasArrived = false;
            
            sf::Vector2f m_normalized;
            
            sf::View m_camera;
           
            bool isSuccess;
            
            sf::Clock m_clockApparition;
    };
}
