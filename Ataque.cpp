#include "Ataque.hpp"
#include <iostream>
#include <math.h>

namespace Zenon{
    
    Ataque::Ataque(GameDataRef l_data, sf::Vector2f l_position):m_data(l_data)
    {
        m_mainSprite.setTexture(m_data->assets.GetTexture("torreta"));
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2,m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_position);
        m_is_attacking = false;
        

    }
    
    void Ataque::Update(float dt)
    {
        for(int i=0;i<m_bala.size();i++){
            m_bala.at(i)->Update(dt);  
        }
        std::cout<<m_bala.size()<<std::endl;
    }
    void Ataque::Draw()
    {
        for(int i=0;i<m_bala.size();i++){
            m_bala.at(i)->Draw();  
        }
        m_data->window.draw(m_mainSprite);
    }
    
    bool Ataque::IsAttacking()
    {
        return m_is_attacking;
    }
    
    void Ataque::FindTarget(std::vector<Enemigo*> &l_enemys)
    {
        for(int i = 0; i<l_enemys.size(); i++)
        {
            if(!m_is_attacking)
            {
                if(m_mainSprite.getPosition().x-l_enemys.at(i)->GetPosition().x < 200 && m_mainSprite.getPosition().y-l_enemys.at(i)->GetPosition().y < 200 && 
                    l_enemys.at(i)->GetPosition().x - m_mainSprite.getPosition().x < 200 && l_enemys.at(i)->GetPosition().y-m_mainSprite.getPosition().y < 200 ||
                        m_mainSprite.getPosition().x-l_enemys.at(i)->GetPosition().x < 200 && m_mainSprite.getPosition().y-l_enemys.at(i)->GetPosition().y < -200 && 
                            l_enemys.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -200 && l_enemys.at(i)->GetPosition().y-m_mainSprite.getPosition().y < -200    )
                {
                    m_target = l_enemys.at(i);
                    std::cout<<"Ya lo tengo"<<std::endl;
                    m_is_attacking = true;
                }
            }
        
        }
        
    }
    
    void Ataque::Attack()
    {
        if(m_is_attacking)
        {
            if(m_mainSprite.getPosition().x-m_target->GetPosition().x < 200 && m_mainSprite.getPosition().y-m_target->GetPosition().y < 200 && 
                   m_target->GetPosition().x - m_mainSprite.getPosition().x < 200 && m_target->GetPosition().y-m_mainSprite.getPosition().y < 200)
            {
                float angle=0;
                float hipotenusa;
                float PI= 3.14159265;
                float incremento_x,incremento_y;

                hipotenusa=sqrt(pow(m_mainSprite.getPosition().x-m_target->GetPosition().x,2)+pow(m_mainSprite.getPosition().y-m_target->GetPosition().y,2));
                angle = asin (abs(m_mainSprite.getPosition().y-m_target->GetPosition().y)/hipotenusa) * 180.0 / PI;
                angle=angle-90;
                
               if(m_mainSprite.getPosition().x-m_target->GetPosition().x<0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y>0){//primer cuadrante
                  
               angle=angle*-1;
               
               m_direccion_sentido.x=(m_target->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y= m_target->GetPosition().y- m_mainSprite.getPosition().y;

               }
               if(m_mainSprite.getPosition().x-m_target->GetPosition().x>0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y<0){// tercer cuadrante

               angle=180-angle;
               m_direccion_sentido.x=m_target->GetPosition().x - m_mainSprite.getPosition().x;
               m_direccion_sentido.y=m_target->GetPosition().y - m_mainSprite.getPosition().y;
               }

               if(m_mainSprite.getPosition().x-m_target->GetPosition().x<=0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y<=0){ //cuarto cuadrante

               angle=angle-180;
               m_direccion_sentido.x=(m_target->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y=m_target->GetPosition().y - m_mainSprite.getPosition().y;
               }
                
               if(m_mainSprite.getPosition().x-m_target->GetPosition().x>0 &&  m_mainSprite.getPosition().y-m_target->GetPosition().y>0){ //cuarto cuadrante

               m_direccion_sentido.x=(m_target->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y=(m_target->GetPosition().y- m_mainSprite.getPosition().y);
               }
                m_mainSprite.setRotation(angle);
           //     m_bullet->Shoot(angle,incremento_x,incremento_y);
                
                if(shoot_time.getElapsedTime().asSeconds() > 0.5)
                {
                    Bala * c_bala= new Bala(m_data,m_mainSprite.getPosition(),m_direccion_sentido,angle);
                    m_bala.push_back(c_bala);
                    shoot_time.restart();
                }

            }
            else
            {
                std::cout<<"Dejo de atacar"<<std::endl;
                m_mainSprite.setRotation(0);
                m_is_attacking = false;
            }

        }
    }
    

       
    

}