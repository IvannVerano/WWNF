#pragma once
#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace Zenon{
 
    class Enemigo{
       
    public:
        Enemigo(GameDataRef l_data, sf::Vector2f l_position);
        void Update(float dt);
        void Draw();
        sf::Vector2f GetPosition();
        
    
    private:
        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_position;     
    }; 
}