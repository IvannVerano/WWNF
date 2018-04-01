
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {

    }

    void SplashState::Init() 
    {
        _data->assets.LoadTexture("Heroe", SPRITESHEET_HEROE);
        _data->assets.LoadTexture("GUI", SPRITESHEET_GUI);
        m_hero = new Hero(_data);
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->_data->window.close();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_hero->IsClicked())
                {
                    m_hero->Select();
                    std::cout<<"Me seleccionas"<<std::endl;
                }
                else
                {
                    if(m_hero->IsSelected())
                    {
                        m_hero->OrderMovement((sf::Vector2f)_data->input.GetMousePosition(_data->window));
                        std::cout<<"Me ordenas moverme"<<std::endl;
                    }
                }
            }
        }
    }

    void SplashState::Update(float dt) {

        m_hero->Update(dt);

    }

    void SplashState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);

        //this->_data->window.draw(this->_background);
        
        m_hero->Draw();

        this->_data->window.display();
    }
}

