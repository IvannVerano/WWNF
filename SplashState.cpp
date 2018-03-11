
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "Trampa.hpp"
#include "Ataque.hpp"
#include "Defensa.hpp"
#include "HUD.hpp"
#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : m_data(data) {

    }

    void SplashState::Init() 
    {
       m_data->assets.LoadTexture("No_trampa", NO_TRAP_SPRITE);
       m_data->assets.LoadTexture("Metralleta", METRALLETA_SPRITE);
       m_data->assets.LoadTexture("Defensa", DEFENSA_SPRITE);
       m_data->assets.LoadTexture("MetralletaS", ATAQUE_HIGHLIGHT);
       m_data->assets.LoadTexture("DefensaS", DEFENSA_HIGHLIGHT);

       int i = 60;
       for(int x = 0; x<3; x++)
       {
            Placer* plaser = new Placer(m_data, sf::Vector2f(80*x+200, i));
            m_placer.push_back(plaser);
            i += 60;
       }
       m_trampa = -1;
       
       m_hud = new HUD(m_data);
       m_noCompruebes = false;
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->m_data->window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_hud->CheckClick())
                {
                    m_trampa = m_hud->GetClick();
                    std::cout<<m_trampa<<std::endl;
                }
                for(int i = 0; i<m_placer.size(); i++)
                {
                    if(m_placer.at(i)->Clicked())
                    {
                        if(m_trampa == 1)
                        {
                            std::cout<<m_trampa<<std::endl;
                            Trampa* tramp = new Ataque(m_data, m_placer.at(i)->GetPosicion());
                            m_trampas.push_back(tramp);
                        }
                        else if(m_trampa == 2)
                        {
                            std::cout<<m_trampa<<std::endl;
                            Trampa* tramp = new Defensa(m_data, m_placer.at(i)->GetPosicion());
                            m_trampas.push_back(tramp);
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                m_trampa = 1;
                std::cout<<"Cambio a metralletas"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                m_trampa = 2;
                std::cout<<"Cambio a Defensa"<<std::endl;
            }
        }
    }

    void SplashState::Update(float dt) {

        for(int i=0; i<m_trampas.size() ; i++)
        {
            m_trampas.at(i)->Update(dt);
        }

    }

    void SplashState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);

        this->m_data->window.draw(this->_background);
        
        for(int i = 0; i<m_placer.size(); i++)
        {
            m_placer.at(i)->Draw();
        }
        
        for(int i = 0; i<m_trampas.size(); i++)
        {
            m_trampas.at(i)->Draw();
        }
        
        m_hud->Draw();

        this->m_data->window.display();
    }
}

