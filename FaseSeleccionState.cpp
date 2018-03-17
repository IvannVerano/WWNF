#include <sstream>
#include "FaseSeleccionState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "SplashState.hpp"
#include <iostream>

namespace Zenon {

    FaseSeleccionState::FaseSeleccionState(GameDataRef data) : m_data(data) 
    {

    }

    void FaseSeleccionState::Init() 
    {
        m_data->assets.LoadTexture("No_trampa", NO_TRAP_SPRITE);
        m_data->assets.LoadTexture("Metralleta", METRALLETA_SPRITE);
        m_data->assets.LoadTexture("Defensa", DEFENSA_SPRITE);
        m_data->assets.LoadTexture("MetralletaS", ATAQUE_HIGHLIGHT);
        m_data->assets.LoadTexture("DefensaS", DEFENSA_HIGHLIGHT);
        m_data->assets.LoadTexture("GUI_METRALLETA", GUI_METRALLETA);
        m_data->assets.LoadTexture("GUI_METRALLETA_SEL", GUI_METRALLETA_SEL);
        m_data->assets.LoadTexture("GUI_DEFENSA", GUI_DEFENSA);
        m_data->assets.LoadTexture("GUI_DEFENSA_SEL", GUI_DEFENSA_SEL);
        m_data->assets.LoadTexture("GUI_ELEMENTS", GUI_ELEMENTS);
        m_boton.setTexture(m_data->assets.GetTexture("Metralleta"));
        m_boton.setOrigin(m_boton.getGlobalBounds().width/2, m_boton.getGlobalBounds().height/2);
        m_boton.setPosition(600,400);
        
        FichaTrampa * metralleta = new FichaTrampa(m_data, m_data->assets.GetTexture("Metralleta"), m_data->assets.GetTexture("MetralletaS"), m_data->assets.GetTexture("GUI_METRALLETA"),m_data->assets.GetTexture("GUI_METRALLETA_SEL"), 1, sf::Vector2f(150,150));
        FichaTrampa * defensa = new FichaTrampa(m_data, m_data->assets.GetTexture("Defensa"), m_data->assets.GetTexture("DefensaS"), m_data->assets.GetTexture("GUI_DEFENSA"),m_data->assets.GetTexture("GUI_DEFENSA_SEL"), 2, sf::Vector2f(400,150));
        
        m_trampasdisp.push_back(metralleta);
        m_trampasdisp.push_back(defensa);
    }

    void FaseSeleccionState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->m_data->window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for(int i = 0; i < m_trampasdisp.size(); i++)
                {
                    if(m_trampasdisp.at(i)->IsClicked())
                    {
                        m_trampasdisp.at(i)->GestionSeleccion();
                    }
                }
                
            }
            
            if(this->m_data->input.IsSpriteClicked(this->m_boton, sf::Mouse::Left, m_data->window))
            {
                this->ChangeState();
            }
        }
    }

    void FaseSeleccionState::Update(float dt) {
            

    }

    void FaseSeleccionState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);
        
        for(int i= 0; i<m_trampasdisp.size(); i++)
        {
            m_trampasdisp.at(i)->Draw();
        }
        
        this->m_data->window.draw(m_boton);
        this->m_data->window.display();
    }
    
    void FaseSeleccionState::ChangeState()
    {
        for(int i = 0; i< m_trampasdisp.size(); i++)
        {
            if(m_trampasdisp.at(i)->IsSelected())
                m_trampasSel.push_back(m_trampasdisp.at(i));
        }
        
        if(m_trampasSel.size()>0)
        {
            m_data->machine.AddState(StateRef(new SplashState(this->m_data, m_trampasSel)));
        }    
    }
}