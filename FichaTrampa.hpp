
#pragma once
#include "Game.hpp"
#include <SFML/Graphics.hpp>
namespace Zenon
{
    class FichaTrampa
    {
        public:
            FichaTrampa(GameDataRef l_data, sf::Texture l_posicion, sf::Texture l_texHighlight, sf::Texture l_gui_defecto, sf::Texture l_gui_sel, int l_tipo, sf::Vector2f l_posicion_gui); 
            void Draw();
            void GestionSeleccion();
            bool IsSelected();
            bool IsClicked();
            sf::Texture &GetTexturaPosicion();
            sf::Texture &GetTexturaHighlight();
            int GetTipo();
        protected:
            GameDataRef m_datos;
            sf::Sprite m_mainSprite;
            sf::Texture m_texturaPosicion;
            sf::Texture m_texturaHighlight;
            sf::Texture m_textura_gui_defecto;
            sf::Texture m_textura_gui_seleccionado;
            int m_tipo;
            bool m_gui_seleccionado;
            
            
    };
}

