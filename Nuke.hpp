#pragma once
#include "Trampa.hpp"
#include "Game.hpp"
#include "Enemy.hpp"

namespace Zenon
{
    class Nuke: public Trampa
    {
        public:
            Nuke(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_texture, const std::vector<Enemy*> &l_enemies);
            void Update(float dt);
            void AnimateApparition();
            void FindTarget();

            void Draw();
        
        private:
            GameDataRef m_data;
            const std::vector<Enemy*> &m_enemies;
            sf::Clock m_ShootCadence;
            float m_timeAparicion;
            int m_rango;
            float m_percentaje;
            int m_price;

            
    };
}