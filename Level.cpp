#include "Level.hpp"

namespace Zenon
{
    Level::Level(GameDataRef l_data, sf::Vector2f l_location, sf::Vector2f l_locationSmall, std::string l_name, sf::Vector2f l_return):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("MapMarker"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_locationSmall);
        m_mainSprite.scale(0.8,0.8);
        const char* level = "definitivo12.tmx";
        m_levels.push_back(level);
        m_LevelName = l_name;
        m_location = l_location;
        m_return = l_return;
        m_container.setTexture(m_data->assets.GetTexture("Folder"));
        m_container.setOrigin(m_container.getGlobalBounds().width/2, m_container.getGlobalBounds().height/2);
        m_container.scale(0.9,0.5);
        
    }
    
    void Level::SetPanicLevel(int l_position)
    {
        m_panicLevel = m_data->reward.GetPanicIncrease(l_position);
    }
   
    void Level::SetPanic(int quantiy)
    {
        m_panicLevel = quantiy;
    }
    
    void Level::CreateLevelRewards()
    {
        m_civilians = 250 * m_panicLevel;
        m_money = (rand()%5) * m_panicLevel;
        
        if (m_panicLevel > 0)
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
        
        m_info.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_info.setPosition(720, 600);
        m_info.setCharacterSize(22);
        m_info.setString(
            "Recompensa por victoria: " + std::to_string(m_money) + "\n" + 
            "Civiles en peligro: " + std::to_string(m_civilians) + "\n" +
            "Nivel de confianza por victoria: " + std::to_string(m_confidenceReward) + "\n"
        );
        
        switch(m_idTrapReward)
            {
                case 3:
                    m_info.setString(m_info.getString() + "Desbloqueas: Cristal de sanacion");
                break;
                case 4:
                    m_info.setString(m_info.getString() +"Desbloqueas: Lanzallamas");
                break;
                case 5:
                    m_info.setString(m_info.getString() +"Desbloqueas: Adrenalina en gas");
                break;
                case -1:
                    m_info.setString(m_info.getString() +"No desbloqueas trampas");
                break;
            }
        
        
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
        m_container.setPosition(sf::Mouse::getPosition().x - 200, sf::Mouse::getPosition().y);
        m_info.setPosition(m_container.getPosition().x - (m_info.getGlobalBounds().width/2), m_container.getPosition().y - 50) ;
    }
    
    void Level::Draw()
    {
        m_data->window.draw(m_mainSprite);
        if(m_data->input.IsSpriteHovered(m_mainSprite, sf::Mouse::Left, m_data->window))
        {
            m_data->window.draw(m_container);
            m_data->window.draw(m_info);
        }
    }
    
    void Level::SetDataRewards(int l_position)
    {
        m_data->reward.SetReward(m_money, m_idTrapReward, m_civilians, m_confidenceReward, l_position, m_location, m_return);
    }
    
    std::string Level::GetLevelName()
    {
        return m_LevelName;
    }
    
    int Level::GetPanicLevel()
    {
        return m_panicLevel;
    }
    
    sf::Vector2f Level::Getcoordinates()
    {
        return m_location;
    }
    
    sf::Vector2f Level::GetReturn()
    {
        return m_return;
    }
}