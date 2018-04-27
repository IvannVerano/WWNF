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
    FichaTrampa::FichaTrampa(GameDataRef l_data, sf::Texture l_posicion, sf::Texture l_gui_defecto, sf::Texture l_gui_sel, int l_tipo, sf::Vector2f l_posicion_gui,int l_precio,int l_porcentaje, float l_cadencia, int l_rango, int l_refresco, int l_potencia, float l_aparicion, sf::Texture l_descriptive):m_datos(l_data)
    {
        m_texturaPosicion = l_posicion;
        m_textura_gui_defecto = l_gui_defecto;
        m_textura_gui_seleccionado = l_gui_sel;
        m_tipo = l_tipo;
       
        m_mainSprite.setTexture(m_textura_gui_defecto);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.scale(0.5,0.5);
        m_mainSprite.setPosition(l_posicion_gui);
        
        m_descriptivetex = l_descriptive;
        m_descriptive.setTexture(m_descriptivetex);
        m_descriptive.setOrigin(m_descriptive.getGlobalBounds().height/2,m_descriptive.getGlobalBounds().height/2);
        m_descriptive.scale(0.8,0.8);
        m_descriptive.setPosition(200, 500);
        
        m_gui_seleccionado = false;
        m_precio=l_precio;
        
        m_porcentaje=l_porcentaje;
        m_cadencia = l_cadencia;
        m_refresco = l_refresco;  
        m_potencia = l_potencia;
        m_rango = l_rango;
        m_tiempoAparicion = l_aparicion;
        
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
    
    void FichaTrampa::SetLocked(bool l_value)
    {
        m_locked = l_value;
    }
    
    void FichaTrampa::Draw()
    {
        if(!m_locked)
        {
            m_datos->window.draw(m_mainSprite);
        }
        if(m_datos->input.IsSpriteHovered(m_mainSprite, sf::Mouse::Left, m_datos->window))
        {
            m_datos->window.draw(m_descriptive);
        }
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
    int FichaTrampa::GetPrecio()
    {
        return m_precio;
    }
    int FichaTrampa::GetPorcentaje()
    {
        return m_porcentaje;
    }
     bool FichaTrampa::Afordable(int l_pago)
     {
         if(m_precio>l_pago)
         {
             return false;
         }
         return true;
     }
     
     float FichaTrampa::GetCadencia()
     {
         return m_cadencia;
     }
     
     int FichaTrampa::GetPotencia()
     {
         return m_potencia;
     }
     
     int FichaTrampa::GetRefresco()
     {
         return m_refresco;
     }
     
     int FichaTrampa::GetRango()
     {
         return m_rango;
     }
     
     float FichaTrampa::GetAparicion()
     {
         return m_tiempoAparicion;
     }
    
}

