#pragma once
#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>


namespace Zenon{
    
    
    class Bala{
    public: 
        Ataque(GameDataRef l_data, sf::Vector2f l_position);
        void Update(float dt);
        void Draw();
        void FindTarget(std::vector<Enemigo *> &l_enemys);
        bool IsAttacking();
        void Attack();
    private:
        
        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        bool m_is_attacking;
        Enemigo * m_target; 
    };
    
}
