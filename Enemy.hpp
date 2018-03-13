#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "MathHelper.hpp"
#include <vector>
#include <iostream>

namespace Zenon {

    class Enemy {
    public:

        enum TYPE {
            bee = 0, butterfly = 1, boss = 2
        };

        Enemy(GameDataRef l_data, sf::Vector2f l_position);

        ~Enemy() {
        }


        void Update(float dt);
        void Draw();
        void SetPosition();
        void PutDiving();
        void SetCambio();
        void SetPath(std::vector<sf::Vector2f> l_path);
        void SetAlternative(std::vector<sf::Vector2f> l_path);

        sf::FloatRect GetGB();
        TYPE GetType();
        int GetCurrentWP();
        int GetPathEnd();
        bool isDiving();

    private:

        GameDataRef m_data;
        sf::Sprite m_enemySprite;
        TYPE m_type;
        sf::Vector2f m_initialPosition;

        float m_wpX;
        float m_wpY;
        std::vector<sf::Vector2f> m_path;
        std::vector<sf::Vector2f> m_pathA;
        sf::Vector2f m_wp;
        bool m_pathCompleted = false;
        bool m_go = false;
        bool m_cambio = false;
        int m_currentWP = 0 + 1;




    };

}
