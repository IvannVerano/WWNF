#include "LevelSelectorState.hpp"
#include "FaseSeleccionState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    LevelSelectorState::LevelSelectorState(GameDataRef l_data, bool rewardisOn):m_data(l_data)
    {
        if(rewardisOn)
            this->ProcessRewards();
    }
    
    void LevelSelectorState::ProcessRewards()
    {
        m_data->data.AddMoney(m_data->reward.GetMoney());
        m_data->data.SetGeneralPunctuation(m_data->reward.GetCiviliansRescued());
        m_data->data.SetConfidenceLevel(m_data->reward.GetConfidenceRestablish());
        if(m_data->reward.GetIdTrapRewarded()!= -1)
            m_data->data.SetUnlockTrap(false, m_data->reward.GetIdTrapRewarded());
    }
    
    void LevelSelectorState::Init()
    {
        Level * america = new Level(m_data, sf::Vector2f(500,400), "America");
        m_levels.push_back(america);
        
        Level * europe = new Level(m_data, sf::Vector2f(1100, 360), "Europa");
        m_levels.push_back(europe);
        
        Level * asia = new Level(m_data, sf::Vector2f(1400, 450), "Asia");
        m_levels.push_back(asia);
        
        Level * africa = new Level(m_data, sf::Vector2f(1050, 600), "Africa");
        m_levels.push_back(africa);
        
        
        m_background.setTexture(m_data->assets.GetTexture("WorldMap"));
        
        for(int i=0; i<m_levels.size(); i++)
        {
            m_levels[i]->SetPanicLevel(i);
            m_levels[i]->CreateLevelRewards();
        }
        
        m_moneyText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_moneyText.setString(std::to_string(m_data->data.GetMoney()));
        m_moneyText.setCharacterSize(40);
        m_moneyText.setPosition(sf::Vector2f(100, 920));
        
        this->InitPanicLevelGUI();
    }
    
    void LevelSelectorState::HandleInput()
    {
        sf::Event event;
        while (this->m_data->window.pollEvent(event)) 
        {
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
              if(!selected)
              {
                for (int i = 0; i < m_levels.size(); i++) {
                    if (m_levels.at(i)->CheckClick()) 
                    {
                        m_levels[i]->SetDataRewards(i);
                        selected = true;
                        this->ChangeState();
                    }
                }
              }

            }
        }
       
    }
    
    void LevelSelectorState::Update(float dt)
    {
        for(int i=0; i<m_levels.size(); i++)
        {
            m_levels[i]->Update(dt);
        }
    }
    
    void LevelSelectorState::ChangeState()
    {
        m_data->machine.AddState(StateRef(new FaseSeleccionState(this->m_data)));
    }
    
    void LevelSelectorState::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
        m_data->window.draw(m_background);
        for(int i=0; i<m_levels.size(); i++)
        {
            m_levels[i]->Draw();
        }
        for(int i=0; i<m_panicLevels.size(); i++)
        {
            m_data->window.draw(m_panicLevels[i]);
        }
        for(int i=0; i<m_levelNames.size(); i++)
        {
            m_data->window.draw(m_levelNames[i]);
        }
        m_data->window.draw(m_moneyText);
        this->m_data->window.display();
    }
    
    void LevelSelectorState::InitPanicLevelGUI()
    {
        for(int i = 0; i<m_levels.size(); i++)
        {
            sf::RectangleShape rec;
            sf::Text text;
            text.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            text.setString(m_levels[i]->GetLevelName());
            text.setColor(sf::Color::White);
            text.setPosition(100+500*i, 50);
            rec.setSize(sf::Vector2f(m_levels[i]->GetPanicLevel(), 20));
            rec.setPosition(100+500*i, 100);
            if(m_levels[i]->GetPanicLevel() > 70)
            {
                rec.setFillColor(sf::Color::Red);
            }
            else if(m_levels[i]->GetPanicLevel() >= 50)
            {
                rec.setFillColor(sf::Color::Yellow);
            }
            else
            {
                rec.setFillColor(sf::Color::Blue);
            }
            
            m_panicLevels.push_back(rec);
            m_levelNames.push_back(text);
        }
    }
}