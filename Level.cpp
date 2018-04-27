#include "Level.hpp"

namespace Zenon
{
    Level::Level(GameDataRef l_data, sf::Vector2f l_location, std::string l_name):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("MapMarker"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_location);
        const char* level = "definitivo12.tmx";
        m_levels.push_back(level);
        m_LevelName = l_name;
    }
    
    void Level::SetPanicLevel(int l_position)
    {
        m_panicLevel = m_data->reward.GetPanicIncrease(l_position);
    }
   
    
    void Level::CreateLevelRewards()
    {
        m_civilians = 250 * m_panicLevel;
        m_money = (rand()%5) * m_panicLevel;
        
        if (m_panicLevel > 25)
        {
            int probability = rand()%100;
            if(probability>60)
            {
                int trap = (rand()%(4 - 2 + 1)) + 2;
                if(m_data->data.IsTrapUnlocked(trap))
                {
                    this->m_idTrapReward = trap;
                }
                else
                    m_idTrapReward = -1;
            }
            else
                m_idTrapReward = -1;
        }
        else
            m_idTrapReward = -1;
        
        m_confidenceReward = rand()%2;
        std::cout<<"//////////////PAIS///////////////"<<std::endl;
        std::cout<<"Money de recompensa: "<<m_money<<std::endl;
        std::cout<<"Civiles rescatados: "<<m_civilians<<std::endl;
        std::cout<<"Nivel de panico: "<<m_panicLevel<<std::endl;
        std::cout<<"Recuperarás: "<<m_confidenceReward<<std::endl;
        std::cout<<"Id de trampa que recuperas: "<<m_idTrapReward<<std::endl;
        std::cout<<"/////////////////////////////"<<std::endl;
    }
    
    bool Level::CheckClick()
    {
        if(m_data->input.IsSpriteClicked(m_mainSprite, sf::Mouse::Left, m_data->window))
        {
            std::cout<<"Clickas el sprite"<<std::endl;
            return true;
        }
        return false;
    }
    
    void Level::Update(float dt)
    {
        m_mainSprite.rotate(2);
    }
    
    void Level::Draw()
    {
        m_data->window.draw(m_mainSprite);
    }
    
    void Level::SetDataRewards(int l_position)
    {
        m_data->reward.SetReward(m_money, m_idTrapReward, m_civilians, m_confidenceReward, l_position);
    }
    
    std::string Level::GetLevelName()
    {
        return m_LevelName;
    }
    
    int Level::GetPanicLevel()
    {
        return m_panicLevel;
    }
}