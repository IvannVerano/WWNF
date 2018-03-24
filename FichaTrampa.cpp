/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FichaTrampa.cpp
 * Author: antonio
 * 
 * Created on 12 de marzo de 2018, 16:10
 */

#include "FichaTrampa.hpp"
#include <iostream>
namespace Zenon
{
    FichaTrampa::FichaTrampa(GameDataRef l_data, sf::Texture l_posicion, sf::Texture l_gui_defecto, sf::Texture l_gui_sel, int l_tipo, sf::Vector2f l_posicion_gui):m_datos(l_data)
    {
        m_texturaPosicion = l_posicion;
        m_textura_gui_defecto = l_gui_defecto;
        m_textura_gui_seleccionado = l_gui_sel;
        m_tipo = l_tipo;
        m_mainSprite.setTexture(m_textura_gui_defecto);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.scale(0.5,0.5);
        m_mainSprite.setPosition(l_posicion_gui);
        m_gui_seleccionado = false;
    }
    
    void FichaTrampa::GestionSeleccion()
    {
        if(m_gui_seleccionado)
        {
            std::cout<<"Cambio la trampa a false"<<std::endl;
            m_mainSprite.setTexture(m_textura_gui_defecto);
            m_gui_seleccionado = false;
        }
        else
        {
            std::cout<<"Cambio la trampa a true"<<std::endl;
            m_mainSprite.setTexture(m_textura_gui_seleccionado);
            m_gui_seleccionado = true;
        }
    }
    
    bool FichaTrampa::IsSelected()
    {
        return m_gui_seleccionado;
    }
    
    bool FichaTrampa::IsClicked()
    {
        if(m_datos->input.IsSpriteClicked(m_mainSprite, sf::Mouse::Left, m_datos->window))
        {
            return true;
        }
        return false;
    }
    
    void FichaTrampa::Draw()
    {
        m_datos->window.draw(m_mainSprite);
    }
    
    
    sf::Texture &FichaTrampa::GetTexturaHighlight()
    {
        return m_textura_gui_seleccionado;
    }
    
    sf::Texture &FichaTrampa::GetTexturaGUI()
    {
        return m_textura_gui_defecto;
    }
    
    
    sf::Texture &FichaTrampa::GetTexturaPosicion()
    {
        return m_texturaPosicion;
    }
    
    int FichaTrampa::GetTipo()
    {
        return m_tipo;
    }
    
}

