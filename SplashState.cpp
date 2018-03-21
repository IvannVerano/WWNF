
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {

    }

    void SplashState::Init() {
        _data->assets.LoadTexture("torreta",TURRET_SPRITE_PATH);
        m_torreta= new Ataque(_data,sf::Vector2f(_data->window.getSize().x/2,_data->window.getSize().y/2));

        _data->assets.LoadTexture("enemigo",ENEMY_SPRITE_PATH);
        Enemigo * c_enemigo= new Enemigo(_data,sf::Vector2f(50,150));
        m_enemigos.push_back(c_enemigo);
        
        _data->assets.LoadTexture("bullet",BULLET_SPRITE_PATH);
     //   m_bullet= new Bala(_data,sf::Vector2f(m_torreta->GetPosition()));
      
    }

    void SplashState ::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->_data->window.close();
            }
        }
    }

    void SplashState::Update(float dt) {

        for(int i= 0; i<m_enemigos.size(); i++)
        {
            m_enemigos.at(i)->Update(dt);
        }
        
        if(m_torreta->IsAttacking() == false)
            m_torreta->FindTarget(m_enemigos);
        else
            m_torreta->Attack();
        
        
        if(m_clock_Spawn.getElapsedTime().asSeconds()>15.0)
        {
           Enemigo * c_newEnemy = new Enemigo(_data,sf::Vector2f(50,150));
           m_enemigos.push_back(c_newEnemy);
           m_clock_Spawn.restart();
        }
        
        m_torreta->Update(dt);
       
        
   /*     
        if(m_clock_Spawn.getElapsedTime().asSeconds()>0.5)
        {
           Bala * c_newBullet = new Bala(_data,sf::Vector2f(m_torreta->GetPosition()));
           m_bullet.push_back(c_newBullet);
           m_clock_Spawn.restart();
        }
     */   
        
         

    }

    void SplashState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);
        
        
        m_torreta->Draw();
        for(int i = 0; i<m_enemigos.size(); i++)
        {
            m_enemigos.at(i)->Draw();
        }
        
     /*   
        for(int i = 0; i<m_bullet.size(); i++)
        {
            m_bullet.at(i)->Draw();
        }
       */ 
        
        
        
        
        this->_data->window.draw(this->_background);

        this->_data->window.display();
    }
}

