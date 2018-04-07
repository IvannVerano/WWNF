#pragma once
#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "MathHelper.hpp"

namespace Zenon {

    class Enemigo {
    public:
        Enemigo(GameDataRef l_data, sf::Vector2f l_position,
                const std::vector<Enemigo*>& l_neighbors, const std::vector<Bezier>& l_routes, int l_path);
        ~Enemigo();

        void Update(float dt);
        void Draw();

        void LoadLives();

        void SetKiller(int l_killer);
        void TakeDamage(int l_damage);
        void SlowDown(float l_factor);
        void NoEffect(float l_factor);
        void CheckRoutes();

        sf::Vector2f GetPosition();
        int GetActualState();
        int GetKiller();
        int GetID();
        bool GetSlowed();
        const sf::Sprite &GetSprite() const;

    private:

        GameDataRef m_data;

        sf::Sprite m_mainSprite;
        sf::Vector2f m_position;
        sf::RectangleShape m_vidaDraw;

        const int m_id;
        int m_state;
        int m_life;
        int m_killer;
        int m_currentWP = 0 + 1;
        int m_randNumber = 0;
        float m_speed;

        static int ID() {
            static int ID = 0;
            return ID++;
        }

        bool m_pathCompleted = false;
        bool m_slowed;

        const std::vector<Enemigo*>& m_neighbors;
        Bezier m_path;
        const std::vector<Bezier>& m_routes;
    };
}

