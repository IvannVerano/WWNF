
#pragma once
#include "Trampa.hpp"
#include "Hero.hpp"
#include <SFML/Graphics.hpp>

namespace Zenon
{
    class Support : public Trampa
    {
        public:
            Support(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Hero*> &l_heroes,int l_rango);
            void Draw();
            void Update(float dt);
            void AnimateApparition();
            int CalculateRec(int l_sum);
            void Act();
        private:
            const std::vector<Hero*> &m_hero;
            int m_rango;
            sf::Clock m_time;

            
    };
}