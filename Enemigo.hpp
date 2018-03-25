#pragma once
#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace Zenon{
 
    class Enemigo{
       
    public:
        Enemigo(GameDataRef l_data, sf::Vector2f l_position, int i, float l_speed);
        void Update(float dt);
        void Draw();
        sf::Vector2f GetPosition();
        void TakeDamage(int l_damage);
        int GetActualState();
        const sf::Sprite &GetSprite() const;
        ~Enemigo();
        int GetID();
        void SetKiller(int l_killer);
        int GetKiller();
        void SlowDown(float l_factor);
        void NoEffect(float l_factor);
        bool GetSlowed();
        
    
    private:
        GameDataRef m_data;
        sf::Sprite m_mainSprite;
        sf::Vector2f m_position;
        sf::RectangleShape m_vidaDraw;
        int m_state;
        int m_life;
        int id;
        int m_killer;
        float m_speed;
        bool m_slowed;
    }; 
}

