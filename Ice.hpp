#pragma once
#include "Trampa.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include "MathHelper.hpp"

namespace Zenon
{
    class Ice: public Trampa
    {
        public:
            Ice(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_texture, const std::vector<Enemy*> &l_enemies);
            void SetAttributes(int l_id, float l_cadence, float l_apptime, int l_power, int l_range, int l_refresh, int l_wait, int l_percentaje, int l_price);
            void Update(float dt);
            void FindTarget();

        private:
            GameDataRef m_data;
            int m_target;
            const std::vector<Enemy*> &m_enemies;
            sf::Clock m_ShootCadence;
            int m_id;
            float m_cadencia;
            float m_timeAparicion;
            int m_potencia;
            int m_rango;
            int m_refresco;
            int m_espera;
            float m_percentaje;
            int m_price;
            int m_realID;
            
    };
}