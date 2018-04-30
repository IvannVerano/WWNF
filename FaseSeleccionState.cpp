#include <sstream>
#include "FaseSeleccionState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "SplashState.hpp"
#include "SaveData.hpp"
#include <iostream>

namespace Zenon {

    FaseSeleccionState::FaseSeleccionState(GameDataRef data) : m_data(data) {

    }

    void FaseSeleccionState::Init() {
        
        m_boton.setTexture(m_data->assets.GetTexture("Metralleta"));
        m_boton.setOrigin(m_boton.getGlobalBounds().width / 2, m_boton.getGlobalBounds().height / 2);
        m_boton.setPosition(800, 400);

        FichaTrampa * metralleta = new FichaTrampa(m_data, m_data->assets.GetTexture("Metralleta"), m_data->assets.GetTexture("GUI_METRALLETA"), m_data->assets.GetTexture("GUI_METRALLETA_SEL"), m_data->assets.GetTexture("GUI_METRALLETA_BLOCK"), 1, sf::Vector2f(150, 150), PRECIO_TORRETA, PORCENTAJE_TORRETA, CADENCIA_TORRETA, RANGO_TORRETA, REFRESCO_TORRETA, POTENCIA_TORRETA, ATRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_TURRET"));
        FichaTrampa * ametralladora = new FichaTrampa(m_data, m_data->assets.GetTexture("ametralladora"), m_data->assets.GetTexture("GUI_AMETRALLADORA"), m_data->assets.GetTexture("GUI_AMETRALLADORA_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 1, sf::Vector2f(550, 150), PRECIO_AMETRALLADORA, PORCENTAJE_AMETRALLADORA, CADENCIA_AMETRALLADORA, RANGO_AMETRALLADORA, REFRESCO_AMETRALLADORA, POTENCIA_AMETRALLADORA, ATRAP_MACHINEGUN_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_AMETRALLADORA"));
        FichaTrampa * defensa = new FichaTrampa(m_data, m_data->assets.GetTexture("Defensa"), m_data->assets.GetTexture("GUI_DEFENSA"), m_data->assets.GetTexture("GUI_DEFENSA_SEL"), m_data->assets.GetTexture("GUI_DEFENSA_BLOCK"), 2, sf::Vector2f(350, 150), PRECIO_TORRE_DEFENSA, PORCENTAJE_TORRE_DEFENSA, CADENCIA_TORRE_DEFENSA, RANGO_TORRE_DEFENSA, REFRESCO_TORRE_DEFENSA, POTENCIA_TORRE_DEFENSA, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_DEFENSE"));
        FichaTrampa * lanzallamas=new FichaTrampa(m_data, m_data->assets.GetTexture("lanzallamas"),m_data->assets.GetTexture("GUI_LANZALLAMAS"),m_data->assets.GetTexture("GUI_LANZALLAMAS_SEL"), m_data->assets.GetTexture("GUI_LANZALLAMAS_BLOCK"),3,sf::Vector2f(750, 150), PRECIO_LANZALLAMAS,PORCENTAJE_LANZALLAMAS,CADENCIA_LANZALLAMAS,RANGO_LANZALLAMAS,REFRESCO_LANZALLAMAS,POTENCIA_LANZALLAMAS,ATRAP_MACHINEGUN_APPEARING_TIME,m_data->assets.GetTexture("DESCRIPTIVE_AMETRALLADORA"));
        FichaTrampa * sanacion=new FichaTrampa(m_data, m_data->assets.GetTexture("sanacion"),m_data->assets.GetTexture("GUI_SANACION"),m_data->assets.GetTexture("GUI_SANACION_SEL"), m_data->assets.GetTexture("GUI_SANACION_BLOCK"),4,sf::Vector2f(150, 500), PRECIO_SANACION,PORCENTAJE_SANACION,CADENCIA_SANACION,RANGO_SANACION,REFRESCO_SANACION,POTENCIA_SANACION, DTRAP_APPEARING_TIME,m_data->assets.GetTexture("DESCRIPTIVE_SANACION"));
        
        m_trampasdisp.push_back(metralleta);
        m_trampasdisp.push_back(defensa);
        m_trampasdisp.push_back(ametralladora);
        m_trampasdisp.push_back(lanzallamas);
        m_trampasdisp.push_back(sanacion);
        
        for(int i=0; i<m_trampasdisp.size(); i++)
        {
            m_trampasdisp[i]->SetLocked(m_data->data.IsTrapUnlocked(i));
        }

        m_dineroJugador = 500;

    }

    void FaseSeleccionState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->m_data->window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (int i = 0; i < m_trampasdisp.size(); i++) {
                    if (m_trampasdisp.at(i)->IsClicked()) {
                        m_trampasdisp.at(i)->GestionSeleccion();
                    }
                }

            }

            if (this->m_data->input.IsSpriteClicked(this->m_boton, sf::Mouse::Left, m_data->window)) {
                this->ChangeState();
            }
        }
    }

    void FaseSeleccionState::Update(float dt) {


    }

    void FaseSeleccionState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);

        for (int i = 0; i < m_trampasdisp.size(); i++) {
            m_trampasdisp.at(i)->Draw();
        }

        this->m_data->window.draw(m_boton);
        this->m_data->window.display();
    }

    void FaseSeleccionState::ChangeState() {
        for (int i = 0; i < m_trampasdisp.size(); i++) 
        {
            if (m_trampasdisp.at(i)->IsSelected())
                m_trampasSel.push_back(m_trampasdisp.at(i));
        }
        
        std::cout<<"Cuando salgo del FaseSeleccion, hay: "<<m_trampasSel.size()<<std::endl;

        if (m_trampasSel.size() > 0) {
            m_data->machine.AddState(StateRef(new SplashState(this->m_data, m_trampasSel, m_dineroJugador)));
        }
    }
}