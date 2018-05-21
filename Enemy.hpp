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
            base = 0, doxy = 1, berseker = 2, hydra = 3, segmento = 4, trapper = 5
        };

        Enemy(GameDataRef l_data, Enemy::TYPE l_type, sf::Vector2f l_position, const std::vector<Enemy*>& l_neighbors);

        ~Enemy() {
        }

        virtual void Update(float dt);
        virtual void Draw();
        void SetPosition();
        void TakeDamage(int l_factor);
        void SetKiller(int l_killer);

        const int GetId();
        float GetDyingTime();
        Enemy::TYPE GetType();
        const sf::Sprite &GetSprite() const;
        sf::FloatRect GetGB();
        sf::Vector2f GetPosition();

        int GetKiller();
        int GetActualState();

        void ResizeLifeIndicator();

    protected:

        const int m_enemyId;
        Enemy::TYPE m_type;

        static int ID() {
            static int ID = 0;
            return ID++;
        }

        GameDataRef m_data;
        sf::Sprite m_enemySprite;
        sf::RectangleShape m_lifeIndicator;
        sf::RectangleShape m_redIndicator;
        sf::Clock m_dyingClock;
        const std::vector<Enemy*>& m_neighbors;
        int m_life;
        int m_startLife;
        int m_state;
        int m_killer;

    };
}