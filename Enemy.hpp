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

        Enemy(GameDataRef l_data, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors);

        ~Enemy() {
        }

        void Update(float dt);
        void Draw();
        void SetPosition();
        void PutDiving();
        void SetCambio();
        void SetPath(std::vector<sf::Vector2f> l_path);
        void SetAlternative(std::vector<sf::Vector2f> l_path);

        const int GetId();
        sf::FloatRect GetGB();
        TYPE GetType();
        int GetCurrentWP();
        int GetPathEnd();
        bool isDiving();
        sf::Sprite & GetSprite();

    private:

        const int m_enemyId;

        static int ID() {
            static int ID = 0;
            return ID++;
        }

        GameDataRef m_data;

        sf::Sprite m_enemySprite;
        sf::Vector2f m_initialPosition;
        TYPE m_type;

        float m_wpX;
        float m_wpY;
        int m_currentWP = 0 + 1;
        std::vector<sf::Vector2f> m_path;
        std::vector<sf::Vector2f> m_pathA;
        const std::vector<Enemy*>& m_neighbors;
        sf::Vector2f m_wp;
        bool m_pathCompleted = false;
        bool m_go = false;
        bool m_cambio = false;

    };
}

