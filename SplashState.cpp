
#include <sstream>
#include "SplashState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "Trampa.hpp"
#include "Ataque.hpp"
#include "Defensa.hpp"
#include "HUD.hpp"
#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data, std::vector<FichaTrampa*> l_fichaTrampa) : m_data(data) 
    {
        m_trampasSel = l_fichaTrampa;
    }

    void SplashState::Init() 
    {
       std::cout<<"Tienes " << m_trampasSel.size()<<" trampas"<<std::endl;
       int i = 60;
       for(int x = 0; x<4; x++)
       {
            Placer* plaser = new Placer(m_data, sf::Vector2f(80*x+100+i, 150));
            m_placer.push_back(plaser);
            i += 60;
       }
       m_trampa = -1;
       
       m_hud = new HUD(m_data, m_trampasSel);
       m_noCompruebes = false;
       
       m_mouseConstruct.setTexture(m_data->assets.GetTexture("CURSOR_BUILD"));
       m_mouseConstruct.setOrigin(m_mouseConstruct.getGlobalBounds().width/2,m_mouseConstruct.getGlobalBounds().height/2);
       m_mouseConstruct.scale(0.7,0.7);
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
                    if(m_placer.at(i)->Clicked(m_trampa))
                    {
                        if(m_trampa> -1)
                        {
                            if(m_trampasSel.at(m_trampa)->GetTipo() == 1)
                            {
                                std::cout<<m_trampa<<std::endl;
                                Trampa* tramp = new Ataque(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion());
                                m_trampas.push_back(tramp);
                            }
                            else if(m_trampasSel.at(m_trampa)->GetTipo() == 2)
                            {
                                std::cout<<m_trampa<<std::endl;
                                Trampa* tramp = new Defensa(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion());
                                m_trampas.push_back(tramp);
                            }
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
        
        int counter = 0;
        for(int i=0; i<m_trampas.size() ; i++)
        {
            m_trampas.at(i)->Update(dt);
        }
        for(int i=0; i<m_placer.size(); i++)
        {
            if(m_placer.at(i)->Hovered() && !m_placer.at(i)->GetOccuped())
            {
                counter++;
            }
        }
        
        if(counter > 0)
            m_hideCursor = true;
        else
            m_hideCursor = false;
        
        m_mouseConstruct.setPosition((sf::Vector2f)m_data->input.GetMousePosition(m_data->window));

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
        
        if(m_hideCursor)
        {
            this->m_data->window.setMouseCursorVisible(false);
            this->m_data->window.draw(m_mouseConstruct);
        }
        else
            this->m_data->window.setMouseCursorVisible(true);

        this->m_data->window.display();
    }
}

