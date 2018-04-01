#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"


namespace Zenon
{
    class Hero
    {
        public:
            Hero(GameDataRef l_data);
            void Update(float dt);
            void Draw();
            void OrderMovement(sf::Vector2f l_destiny);
            void Move(float dt);
            void Select();
            bool IsSelected();
            bool IsClicked();
        private:
            GameDataRef m_data;
            sf::Sprite m_mainSprite;
            bool m_isSelected;
            sf::Vector2f m_direction;
            sf::Sprite m_destinyPointer;
            int m_state;
    };
}