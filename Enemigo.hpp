#pragma once
#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace Zenon{
 
    class Enemigo{
       
    public:
        Enemigo(GameDataRef l_data, sf::Vector2f l_position, int i);
        void Update(float dt);
        void Draw();
        sf::Vector2f GetPosition();
        void TakeDamage(int l_damage);
        int GetActualState();
        const sf::Sprite &GetSprite() const;
        int GetRecuperacion();
        ~Enemigo();
        int GetID();
        
    
    private:
        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_position;
        int m_state;
        int m_life;
        int id;
        int m_recuperacion;
    }; 
}

