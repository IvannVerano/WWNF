
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "Maps.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {
    
    }

    void SplashState::Init() {
        
        const char * michar = "definitivo12.tmx";
        map = new Maps(_data, michar);
        
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->_data->window.close();
            }
        }
    }

    void SplashState::Update(float dt) {



    }

    void SplashState::Draw(float dt) {
        if(!map->IsDrawn())
        {
            this->_data->window.clear(sf::Color::Red);
            this->_data->window.draw(this->_background);
            map->Draw();
        }

        this->_data->window.display();
    }
}
