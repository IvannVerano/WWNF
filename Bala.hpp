#pragma once
#include "Game.hpp"
#include "Enemigo.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace Zenon{
    
    
    class Bala{
    public: 
        Bala(GameDataRef l_data, sf::Vector2f l_position,sf::Vector2f l_enemigo,float l_angulo);
        void Update(float dt);
        void Draw();
        void Shoot(float angulo,float incr_x,float incr_y);
        sf::Vector2f GetPosition();

    private:
        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_positionBullet;
        sf::Vector2f m_direccion;
        float m_angulo;
        bool m_shoot;

    };
    
}
