
#include "DEFINITIONS.hpp"
#include <iostream>
#include <math.h>
#include "Ice.hpp"

namespace Zenon
{
    Ice::Ice(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture& l_texture, const std::vector<Enemy*>& l_enemies):Trampa(l_data), m_enemies(l_enemies)
    {
        m_state = TRAP_STATE_PLACED;
    }
    
    void Ice::SetAttributes(int l_id, float l_cadence, float l_apptime, int l_power, int l_range, int l_refresh, int l_wait, int l_percentaje, int l_price)
    {
        m_id = l_id;      
        m_rango = l_range;  
        m_price = l_price;
    }
    

    
    void Ice::Update(float dt)
    {
        this->FindTarget(); 
    }
    
    void Ice::FindTarget()
    {
        for (int i = 0; i < m_enemies.size(); i++) 
        {
             std::cout<<"CAZADO PAPI "<<i<<std::endl;

        }
    }
    


    
 
    
}