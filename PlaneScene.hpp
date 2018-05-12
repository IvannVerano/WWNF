#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "FichaTrampa.hpp"
#include "SplashState.hpp"
#include "MathHelper.hpp"
#include <SFML/Audio.hpp>

namespace Zenon
{
    class PlaneScene: public State
    {
        public:
            PlaneScene(GameDataRef l_data, std::vector<FichaTrampa*> l_fichaTrampa, sf::Music * l_theme);
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
            sf::Vector2f m_destinyPoint;
            sf::Vector2f m_trajectory;
            bool hasArrived = false;
            std::vector<FichaTrampa*> m_fichaTrampa;
            sf::Music * m_theme;
            sf::SoundBuffer m_bufferSound;
            sf::Sound m_soundPlay;
            sf::Vector2f m_normalized;
            
    };
}