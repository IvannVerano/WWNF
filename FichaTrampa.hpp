
#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
namespace Zenon
{
    class FichaTrampa
    {
        public:
            FichaTrampa(GameDataRef l_data, sf::Texture l_posicion, sf::Texture l_gui_defecto, sf::Texture l_gui_sel, int l_tipo, sf::Vector2f l_posicion_gui,int l_precio, int l_porcentaje, float l_cadencia, int l_rango, int l_refresco, int l_potencia);
            void Draw();
            void GestionSeleccion();
            bool IsSelected();
            bool IsClicked();
            sf::Texture &GetTexturaPosicion();
            sf::Texture &GetTexturaHighlight();
            sf::Texture &GetTexturaGUI();
            int GetTipo();
            int GetPrecio();
            int GetPorcentaje();
            bool Afordable(int l_pago);
            int GetRango();
            int GetPotencia();
            int GetRefresco();
            float GetCadencia();
        protected:
            GameDataRef m_datos;
            sf::Sprite m_mainSprite;
            sf::Texture m_texturaPosicion;
            sf::Texture m_texturaHighlight;
            sf::Texture m_textura_gui_defecto;
            sf::Texture m_textura_gui_seleccionado;
            int m_tipo;
            bool m_gui_seleccionado;
            
            int m_precio;
            int m_porcentaje;
            int m_rango;
            float m_cadencia;
            int m_refresco;
            int m_potencia;
            
    };
}

