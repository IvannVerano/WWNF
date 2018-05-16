
#include "HelpState.hpp"

namespace Zenon{
    HelpState::HelpState(GameDataRef l_data) : m_data(l_data) { 
    }

    HelpState::~HelpState() {

    }
    
    void HelpState::Init(){
        m_HelpBG.setTexture(m_data->assets.GetTexture("HelpBG"));
        m_HelpBG.setOrigin(m_HelpBG.getGlobalBounds().width / 2, m_HelpBG.getGlobalBounds().height / 2);
        m_HelpBG.setPosition(m_data->window.getSize().x/2, m_data->window.getSize().y/2);
       
        m_HelpReturn.setTexture(m_data->assets.GetTexture("HelpReturn"));
        m_HelpReturn.setOrigin(m_HelpReturn.getGlobalBounds().width / 2, m_HelpReturn.getGlobalBounds().height / 2);
        m_HelpReturn.setPosition(200, 80);
        m_HelpReturn.scale(0.8,0.8);
    }
    
    void HelpState::HandleInput(){
        if(m_data->input.IsSpriteClicked(m_HelpReturn, sf::Mouse::Left, m_data->window))
        {
            this->Return();
        }
    }
    
    void HelpState::Update(float dt){
        
    }
    
    void HelpState::Draw(float dt){
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.draw(m_HelpBG);
        this->m_data->window.draw(m_HelpReturn);
        this->m_data->window.display();
    }
    
    void HelpState::Return(){
        m_data->machine.AddState(StateRef(new MainMenuState(this->m_data)));
    }
}


