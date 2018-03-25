

#pragma once
#include "Trampa.hpp"
#include "Enemigo.hpp"
#include "Bala.hpp"
#include <SFML/Graphics.hpp>

namespace Zenon
{
    class Ataque : public Trampa
    {
        public:
            Ataque(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Enemigo*> &l_enemigos,int l_precio, int l_porcentaje, int l_rango, int l_potencia, float l_cadencia, int l_refresco, int l_id, float l_appearing);
            void Draw();
            void Update(float dt);
            void AnimateApparition();
            void FindTarget();
            void Attack();
            bool CheckColision();
            void ResetTarget();
            int CalculateRec(int l_sum);
        private:
            const std::vector<Enemigo*> &m_enemy;
            bool m_is_attacking;
            sf::Clock shoot_time;
            std::vector<Bala*> m_bala;
            int m_target;
            int m_id;
            float m_cadencia;
            float m_timeAparicion;
            int m_potencia;
            int m_rango;
            int m_refresco;
    };
}