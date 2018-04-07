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

        Enemy(GameDataRef l_data, sf::Vector2f l_position,
                const std::vector<Enemy*>& l_neighbors, const std::vector<Bezier>& l_routes, int l_path);

        ~Enemy() {
        }

        void Update(float dt);
        void Draw();
        void SetPosition();
        void PutDiving();
        void SetCambio();
        void SetPath(std::vector<sf::Vector2f> l_path);
        void SetAlternative(std::vector<sf::Vector2f> l_path);

        void checkRoutes();

        const int GetId();
        sf::FloatRect GetGB();
        TYPE GetType();
        int GetCurrentWP();
        Bezier GetPath();
        bool isDiving();
        sf::Vector2f GetPosition();
        int GetNumber();
        void TakeDamage(int l_factor);
        void SetKiller(int l_killer);
        int GetKiller();
        int GetActualState();
        const sf::Sprite &GetSprite() const;

    private:

        const int m_enemyId;

        static int ID() {
            static int ID = 0;
            return ID++;
        }

        GameDataRef m_data;

        sf::Sprite m_enemySprite;
        sf::Vector2f m_resultant;
        std::vector<sf::Vector2f> m_resultantAcc;
        TYPE m_type;

        int m_currentWP = 0 + 1;
        Bezier m_path;
        std::vector<Bezier> m_routes;
        const std::vector<Enemy*>& m_neighbors;
        int l_rNumber = 0;
        bool m_pathCompleted = false;

        int m_life;
        int m_state;
        int m_killer;

    };
}