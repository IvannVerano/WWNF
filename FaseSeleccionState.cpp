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



        m_boton.setTexture(m_data->assets.GetTexture("Metralleta"));
        m_boton.setOrigin(m_boton.getGlobalBounds().width / 2, m_boton.getGlobalBounds().height / 2);
        m_boton.setPosition(800, 400);

        FichaTrampa * metralleta = new FichaTrampa(m_data, m_data->assets.GetTexture("Metralleta"), m_data->assets.GetTexture("GUI_METRALLETA"), m_data->assets.GetTexture("GUI_METRALLETA_SEL"), 1, sf::Vector2f(150, 150), PRECIO_TORRETA, PORCENTAJE_TORRETA, CADENCIA_TORRETA, RANGO_TORRETA, REFRESCO_TORRETA, POTENCIA_TORRETA, ATRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_TURRET"));
        FichaTrampa * ametralladora = new FichaTrampa(m_data, m_data->assets.GetTexture("ametralladora"), m_data->assets.GetTexture("GUI_AMETRALLADORA"), m_data->assets.GetTexture("GUI_AMETRALLADORA_SEL"), 1, sf::Vector2f(550, 150), PRECIO_AMETRALLADORA, PORCENTAJE_AMETRALLADORA, CADENCIA_AMETRALLADORA, RANGO_AMETRALLADORA, REFRESCO_AMETRALLADORA, POTENCIA_AMETRALLADORA, ATRAP_MACHINEGUN_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_AMETRALLADORA"));
        FichaTrampa * defensa = new FichaTrampa(m_data, m_data->assets.GetTexture("Defensa"), m_data->assets.GetTexture("GUI_DEFENSA"), m_data->assets.GetTexture("GUI_DEFENSA_SEL"), 2, sf::Vector2f(350, 150), PRECIO_TORRE_DEFENSA, PORCENTAJE_TORRE_DEFENSA, CADENCIA_TORRE_DEFENSA, RANGO_TORRE_DEFENSA, REFRESCO_TORRE_DEFENSA, POTENCIA_TORRE_DEFENSA, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_DEFENSE"));

        m_trampasdisp.push_back(metralleta);
        m_trampasdisp.push_back(defensa);
        m_trampasdisp.push_back(ametralladora);

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
        for (int i = 0; i < m_trampasdisp.size(); i++) {
            if (m_trampasdisp.at(i)->IsSelected())
                m_trampasSel.push_back(m_trampasdisp.at(i));
        }

        if (m_trampasSel.size() > 0) {
            m_data->machine.AddState(StateRef(new SplashState(this->m_data, m_trampasSel, m_dineroJugador)));
        }
    }
}