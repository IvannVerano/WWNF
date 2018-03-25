/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Defensa.hpp
 * Author: antonio
 *
 * Created on 8 de marzo de 2018, 21:08
 */

#pragma once
#include "Trampa.hpp"
#include "Enemigo.hpp"
#include <SFML/Graphics.hpp>

namespace Zenon
{
    class Defensa : public Trampa
    {
        public:
            Defensa(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Enemigo*> &l_enemigos,int l_rango);
            void Draw();
            void Update(float dt);
            void AnimateApparition();
            int CalculateRec(int l_sum);
            void Act();
        private:
            const std::vector<Enemigo*> &m_enemy;
            int m_rango;

            
    };
}
