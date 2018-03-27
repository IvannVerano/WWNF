/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HUD.hpp
 * Author: antonio
 *
 * Created on 10 de marzo de 2018, 18:28
 */

#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "FichaTrampa.hpp"
#include <vector>

namespace Zenon
{
    class HUD
    {
        public:
            HUD(GameDataRef l_data, std::vector<FichaTrampa*> l_trampas);
            bool CheckClick();
            void Update(float dt);
            void Draw();
            int GetClick();
        
        private:
            GameDataRef m_data;
            std::vector<sf::Sprite> m_options;
            std::vector<sf::Texture> m_texturas_no_highlight;
            std::vector<sf::Texture> m_texturas_highlight;
            int m_clicked;
    };
}
