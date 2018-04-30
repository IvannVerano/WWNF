#include "LevelSelectorState.hpp"
#include "FaseSeleccionState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    LevelSelectorState::LevelSelectorState(GameDataRef l_data, bool rewardisOn):m_data(l_data)
    {
        m_data->assets.LoadTexture("TILESET", TILESET_FILEPATH);
        m_data->assets.LoadTexture("No_trampa", NO_TRAP_SPRITE);
        m_data->assets.LoadTexture("Metralleta", METRALLETA_SPRITE);
        m_data->assets.LoadTexture("Defensa", DEFENSA_SPRITE);
        m_data->assets.LoadTexture("GUI_METRALLETA", GUI_METRALLETA);
        m_data->assets.LoadTexture("GUI_METRALLETA_SEL", GUI_METRALLETA_SEL);
        m_data->assets.LoadTexture("GUI_DEFENSA", GUI_DEFENSA);
        m_data->assets.LoadTexture("GUI_DEFENSA_SEL", GUI_DEFENSA_SEL);
        m_data->assets.LoadTexture("GUI_ELEMENTS", GUI_ELEMENTS);
        m_data->assets.LoadTexture("WHITE_GUI_ELEMENTS", WHITE_GUI_ELEMENTS);
        m_data->assets.LoadTexture("CURSOR_BUILD", CURSOR_BUILD);
        m_data->assets.LoadTexture("enemigo", ENEMY_SPRITE);
        m_data->assets.LoadTexture("berseker", BERSEKER_SPRITE);
        m_data->assets.LoadTexture("bullet", LASER_SPRITE);
        m_data->assets.LoadTexture("ametralladora", AMETRALLADORA_SPRITE);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA", GUI_AMETRALLADORA);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA_SEL", GUI_AMETRALLADORA_SEL);
        m_data->assets.LoadFont("FUENTE_DINERO", FONT_DINERO);
        m_data->assets.LoadTexture("DESCRIPTIVE_TURRET", DESCRIPTIVE_TURRET);
        m_data->assets.LoadTexture("DESCRIPTIVE_DEFENSE", DESCRIPTIVE_DEFENSE);
        m_data->assets.LoadTexture("DESCRIPTIVE_AMETRALLADORA", DESCRIPTIVE_AMETRALLADORA);
        m_data->assets.LoadTexture("point1", POINT1);
        m_data->assets.LoadTexture("tienda", TIENDA);
        m_data->assets.LoadTexture("spawn", SPAWN);
        m_data->assets.LoadTexture("Hero", SPRITESHEET_HEROE);
        m_data->assets.LoadTexture("Hero_GUI", HERO_GUI_POS);
        m_data->assets.LoadTexture("Hero_Face1", SPRITE_HEROE_FACE1);
        m_data->assets.LoadTexture("lanzallamas", LANZALLAMAS_SPRITE);
        m_data->assets.LoadTexture("fire", FIRE_SPRITE);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS", GUI_LANZALLAMAS);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS_SEL", GUI_LANZALLAMAS_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_LANZALLAMAS", DESCRIPTIVE_AMETRALLADORA);
        m_data->assets.LoadTexture("sanacion", SANACION_SPRITE);
        m_data->assets.LoadTexture("GUI_SANACION", GUI_SANACION);
        m_data->assets.LoadTexture("GUI_SANACION_SEL", GUI_SANACION_SEL);
        m_data->assets.LoadTexture("DESCRIPTIVE_SANACION", DESCRIPTIVE_SANACION);
        m_data->assets.LoadTexture("Hydra Sheet", HYDRA_SPRITE_SHEET);
        m_data->assets.LoadTexture("WorldMap", WORLD_MAP);
        m_data->assets.LoadTexture("MapMarker", MARKER);
        m_data->assets.LoadTexture("Herosprite2", SPRITESHEET_HEROE2);
        m_data->assets.LoadTexture("GUI_AMETRALLADORA_BLOCK", GUI_AMETRALLADORA_BLOCK);
        m_data->assets.LoadTexture("GUI_METRALLETA_BLOCK", GUI_METRALLETA_BLOCK);
        m_data->assets.LoadTexture("GUI_DEFENSA_BLOCK", GUI_DEFENSA_BLOCK);
        m_data->assets.LoadTexture("GUI_SANACION_BLOCK", GUI_SANACION_BLOCK);
        m_data->assets.LoadTexture("GUI_LANZALLAMAS_BLOCK", GUI_LANZALLAMAS_BLOCK);
        m_data->assets.LoadTexture("LATERAL_MOV_FIGHTER", SPRITESHEET_LATERAL_MOV1);
        
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