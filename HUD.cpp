/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HUD.cpp
 * Author: antonio
 * 
 * Created on 10 de marzo de 2018, 18:28
 */

#include "HUD.hpp"
#include "DEFINITIONS.hpp"
#include "FichaTrampa.hpp"
#include <iostream>

namespace Zenon
{
    HUD::HUD(GameDataRef l_data, std::vector<FichaTrampa*> l_trampas):m_data(l_data)
    {
        for(int i = 0; i< l_trampas.size(); i++)
        {
            sf::Sprite c_option1;
            m_texturas_no_highlight.push_back(l_trampas.at(i)->GetTexturaGUI());
            m_texturas_highlight.push_back(l_trampas.at(i)->GetTexturaHighlight());
            c_option1.setTexture(l_trampas.at(i)->GetTexturaGUI());
            c_option1.setOrigin(c_option1.getGlobalBounds().width/2, c_option1.getGlobalBounds().height + 100);
            c_option1.setPosition(200*(i+1), 870);
            c_option1.setScale(0.25,0.25);
            m_options.push_back(c_option1);
        }
        m_clicked = -1;
    }
    
    bool HUD::CheckClick()
    {
        bool l_yes = false;
        int l_clicked = -1;
        for(int i = 0; i< m_options.size(); i++)
            {
                if(m_data->input.IsSpriteClicked(m_options.at(i), sf::Mouse::Left, m_data->window))
                {
                    l_clicked = i;
                    l_yes = true;
                }
            }

        this->ProccessSelection(l_clicked);
        
        return l_yes;
    }
    
    void HUD::ProccessSelection(int l_clicked)
    {
        //Reseteo todas las opciones del menú
            if(l_clicked!= -1)
            {
               m_clicked = l_clicked;
               for(int j = 0; j<m_options.size(); j++)
                {
                   m_options.at(j).setTexture(m_texturas_no_highlight.at(j));
                }
               m_options.at(l_clicked).setTexture(m_texturas_highlight.at(l_clicked));
            }
    }
    
    int HUD::GetClick()
    {
        return m_clicked;
    }
    
    void HUD::Update(float dt)
    {}
    
    void HUD::Draw()
    {
        for(int i = 0; i < m_options.size(); i++)
        {
            m_data->window.draw(m_options.at(i));
        }
    }

}

