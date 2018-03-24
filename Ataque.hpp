

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
            Ataque(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Enemigo*> &l_enemigos);
            void Draw();
            void Update(float dt);
            void AnimateApparition();
            void FindTarget();
            void Attack();
            bool CheckColision();
            void ResetTarget();
        private:
            const std::vector<Enemigo*> &m_enemy;
            bool m_is_attacking;
            sf::Clock shoot_time;
            std::vector<Bala*> m_bala;
            int m_target;
            
    };
}