#include "LevelSelectorState.hpp"
#include "FaseSeleccionState.hpp"
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon {

    LevelSelectorState::LevelSelectorState(GameDataRef l_data, bool rewardisOn) : m_data(l_data) {
        if (rewardisOn)
            this->ProcessRewards();
    }

    void LevelSelectorState::ProcessRewards() {
        m_data->data.AddMoney(m_data->reward.GetMoney());
        m_data->data.SetGeneralPunctuation(m_data->reward.GetCiviliansRescued());
        m_data->data.SetConfidenceLevel(m_data->reward.GetConfidenceRestablish());
        if (m_data->reward.GetIdTrapRewarded() != -1)
            m_data->data.SetUnlockTrap(false, m_data->reward.GetIdTrapRewarded());
    }

    void LevelSelectorState::Init() {
       
        Level * america = new Level(m_data, sf::Vector2f(500, 450), sf::Vector2f(630, 350), "America");
        m_levels.push_back(america);

        Level * europe = new Level(m_data, sf::Vector2f(1000, 400), sf::Vector2f(1030, 350), "Europa");
        m_levels.push_back(europe);

        Level * asia = new Level(m_data, sf::Vector2f(1400, 500), sf::Vector2f(1250, 360), "Asia");
        m_levels.push_back(asia);

        Level * africa = new Level(m_data, sf::Vector2f(1000, 500), sf::Vector2f(1030, 460), "Africa");
        m_levels.push_back(africa);


        m_background.setTexture(m_data->assets.GetTexture("WorldMap"));

        for (int i = 0; i < m_levels.size(); i++) {
            m_levels[i]->SetPanicLevel(i);
            m_levels[i]->CreateLevelRewards();
        }

        m_moneyText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_moneyText.setString(std::to_string(m_data->data.GetMoney()));
        m_moneyText.setCharacterSize(35);
        m_moneyText.setPosition(sf::Vector2f(350, 802));

        this->InitPanicLevelGUI();
        
        for(int i = 0; i<m_data->data.GetConfidenceLevel(); i++)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(15, 20));
            rect.setPosition(30*i + 800, 150);
            rect.setFillColor(sf::Color::Green);
            m_confidence.push_back(rect);
        }
    }

    void LevelSelectorState::HandleInput() {
        sf::Event event;
        while (this->m_data->window.pollEvent(event)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!selected) {
                    for (int i = 0; i < m_levels.size(); i++) {
                        if (m_levels.at(i)->CheckClick()) {
                            m_levels[i]->SetDataRewards(i);
                            selected = true;
                            this->ChangeState();
                        }
                    }
                }

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                m_data->window.close();
            }
        }

    }

    void LevelSelectorState::Update(float dt) {
        for (int i = 0; i < m_levels.size(); i++) {
            m_levels[i]->Update(dt);
        }
        if (m_data->data.GetConfidenceLevel() <= 0) {
            this->CallGameOver();
        }
    }

    void LevelSelectorState::CallGameOver() {
        this->m_data->machine.AddState(StateRef(new GameOverState(this->m_data, m_data->data.GetMoney())));
    }

    void LevelSelectorState::ChangeState() 
    {
        this-> m_data->machine.AddState(StateRef(new FaseSeleccionState(this->m_data)));
    }

    void LevelSelectorState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.setView(this->m_data->window.getDefaultView());
        m_data->window.draw(m_background);
        for (int i = 0; i < m_levels.size(); i++) {
            m_levels[i]->Draw();
        }
        for (int i = 0; i < m_panicLevels.size(); i++) {
            m_data->window.draw(m_panicLevels[i]);
        }
        for(int i=0; i<m_confidence.size(); i++)
        {
            m_data->window.draw(m_confidence[i]);
        }
        m_data->window.draw(m_moneyText);
        this->m_data->window.display();
    }

    void LevelSelectorState::InitPanicLevelGUI() {
        for (int i = 0; i < m_levels.size(); i++) {
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(m_levels[i]->GetPanicLevel()+75, 18));
            switch(i)
            {
                case 0:
                    //AMERICA
                    rec.setPosition(115, 329);
                break;
                case 1:
                    //EUROPA
                    rec.setPosition(1593, 329);
                break;
                case 2:
                    //ASIA
                    rec.setPosition(1593, 612);
                break;
                case 3:
                    //AFRICA
                    rec.setPosition(115, 612);
                break;
            }
            if (m_levels[i]->GetPanicLevel() > 70) {
                rec.setFillColor(sf::Color::Red);
            } else if (m_levels[i]->GetPanicLevel() >= 50) {
                rec.setFillColor(sf::Color::Yellow);
            } else {
                rec.setFillColor(sf::Color::Blue);
            }
            m_panicLevels.push_back(rec);
        }
    }
}