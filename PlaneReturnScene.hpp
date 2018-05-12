#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "SplashState.hpp"
#include "MathHelper.hpp"
#include <SFML/Audio.hpp>

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
            void PlaySound();
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
            
            sf::Music * m_theme;
            sf::SoundBuffer m_bufferSound;
            sf::Sound m_soundPlay;
            
            bool hasArrived = false;
            
            sf::Vector2f m_normalized;
            
           
            bool isSuccess;
            bool isSounded = false;
            
            sf::Clock m_clockApparition;
    };
}
