
#include "HelpState.hpp"

namespace Zenon{
    HelpState::HelpState(GameDataRef l_data) : m_data(l_data) {
        
    }

    HelpState::~HelpState() {
    }
    
    void HelpState::Init(){
        
    }
    
    void HelpState::HandleInput(){
        
    }
    
    void HelpState::Update(float dt){
        
    }
    
    void HelpState::Draw(float dt){
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.display();
    }
}


