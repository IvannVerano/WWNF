
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "Trampa.hpp"
#include "Ataque.hpp"
#include "Defensa.hpp"
#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {

    }

    void SplashState::Init() 
    {
       _data->assets.LoadTexture("No_trampa", NO_TRAP_SPRITE);
       _data->assets.LoadTexture("Metralleta", METRALLETA_SPRITE);
       _data->assets.LoadTexture("Defensa", DEFENSA_SPRITE);
       int i = 60;
       for(int x = 0; x<3; x++)
       {
            Placer* plaser = new Placer(_data, sf::Vector2f(80*x+200, i));
            placer.push_back(plaser);
            i += 60;
       }
       trampa = 1;
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->_data->window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for(int i = 0; i<placer.size(); i++)
                {
                    if(placer.at(i)->Clicked())
                    {
                        if(trampa == 1)
                        {
                            Trampa* tramp = new Ataque(_data, placer.at(i)->GetPosicion());
                            trampas.push_back(tramp);
                        }
                        else
                        {
                            Trampa* tramp = new Defensa(_data, placer.at(i)->GetPosicion());
                            trampas.push_back(tramp);
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                trampa = 1;
                std::cout<<"Cambio a metralletas"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                trampa = 2;
                std::cout<<"Cambio a Defensa"<<std::endl;
            }
        }
    }

    void SplashState::Update(float dt) {



    }

    void SplashState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);

        this->_data->window.draw(this->_background);
        
        for(int i = 0; i<placer.size(); i++)
        {
            placer.at(i)->Draw();
        }
        
        for(int i = 0; i<trampas.size(); i++)
        {
            trampas.at(i)->Draw();
        }

        this->_data->window.display();
    }
}

