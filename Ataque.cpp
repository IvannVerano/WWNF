
#include "Ataque.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>

namespace Zenon
{
    Ataque::Ataque(GameDataRef l_data, sf::Vector2f l_posicion, sf::Texture &l_textura, const std::vector<Enemigo*> &l_enemigos,int l_precio,int l_porcentaje, int l_rango, int l_potencia, float l_cadencia, int l_refresco, int l_id, float l_appearing):Trampa(l_data), m_enemy(l_enemigos)
    {
        m_SpriteAnimation.setTexture(m_datos->assets.GetTexture("GUI_ELEMENTS"));
        m_SpriteAnimation.setTextureRect(sf::IntRect(321, 163, 24, 30));
        m_SpriteAnimation.setOrigin(m_SpriteAnimation.getGlobalBounds().width/2, m_SpriteAnimation.getGlobalBounds().height/2);
        m_SpriteAnimation.scale(2.0,2.0);
        m_SpriteAnimation.setPosition(l_posicion.x, l_posicion.y - 50);
        
        m_mainSprite.setTexture(l_textura);
        m_mainSprite.setOrigin(m_mainSprite.getGlobalBounds().width/2, m_mainSprite.getGlobalBounds().height/2);
        m_mainSprite.setPosition(l_posicion);
        
        //Llenamos el vector para animarr
        m_AnimationFramesAppear.push_back(sf::IntRect(321, 163, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(357, 210, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(296, 197, 24, 30));
        m_AnimationFramesAppear.push_back(sf::IntRect(3,6, 24, 30));
        
        //inicializamos variables
        m_aniAppearClock.restart();
        m_timeAppear.restart();
        m_timeAparicion = l_appearing;
        m_animationAppearCounter = 1;
        
        m_state = TRAP_STATE_APPEARING;
        
        m_is_attacking = false;
        m_target = -1;
        m_porcentaje=l_porcentaje;
        
        m_cadencia = l_cadencia;
        m_potencia = l_potencia;
        m_rango= l_rango;
        m_precio = l_precio;
        m_refresco = l_refresco;
        
        m_id = l_id;
        
       
   
    }
    void Ataque::Update(float dt)
    {
        if(m_state == TRAP_STATE_APPEARING)
        {
            this->AnimateApparition();
            if(m_timeAppear.getElapsedTime().asSeconds() > m_timeAparicion)
            {
                m_state = TRAP_STATE_PLACED;
            }
        }
        else
        {
            if(!m_is_attacking && m_target == -1)
            {
                this->FindTarget();
            }
            else
            {
                this->Attack();
            }
            std::cout<<"----------------"<<std::endl;
            for(int i = 0; i<m_enemy.size(); i++)
            {
                std::cout <<m_enemy[i]->GetID()<<": "<<m_enemy[i]->GetActualState()<<std::endl;
            }
            std::cout<<"----------------"<<std::endl;
        }
        
        for(int i=0; i<m_bala.size(); i++)
        {
            m_bala.at(i)->Update(dt);
        }
        
        this->CheckColision();
        
        
    }
    void Ataque::Draw()
    {
        if(m_state == TRAP_STATE_APPEARING)
            m_datos->window.draw(m_SpriteAnimation);
        else
        {
            for(int i = 0; i<m_bala.size(); i++)
            {
                m_bala.at(i)->Draw();
            }
            m_datos->window.draw(m_mainSprite);
        }
    }
    
    void Ataque::AnimateApparition()
    {
        if (m_aniAppearClock.getElapsedTime().asSeconds() > SPEED_ANIMATION / m_AnimationFramesAppear.size())
		{
			if (m_animationAppearCounter < m_AnimationFramesAppear.size() - 1)
			{
				m_animationAppearCounter++;
			}
			else
			{
				m_animationAppearCounter = 0;
			}

			m_SpriteAnimation.setTextureRect(m_AnimationFramesAppear.at(m_animationAppearCounter));

			m_aniAppearClock.restart();
		}
    }
    
    void Ataque::FindTarget()
    {
         for(int i = 0; i<m_enemy.size(); i++)
        {
            if(!m_is_attacking && m_target == -1)
            {
                if(m_mainSprite.getPosition().x-m_enemy.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y-m_enemy.at(i)->GetPosition().y < m_rango && 
                    m_enemy.at(i)->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemy.at(i)->GetPosition().y-m_mainSprite.getPosition().y < m_rango ||
                        m_mainSprite.getPosition().x-m_enemy.at(i)->GetPosition().x < m_rango && m_mainSprite.getPosition().y-m_enemy.at(i)->GetPosition().y < -m_rango && 
                            m_enemy.at(i)->GetPosition().x - m_mainSprite.getPosition().x < -m_rango && m_enemy.at(i)->GetPosition().y-m_mainSprite.getPosition().y < -m_rango    )
                {
                    if(m_enemy[i]->GetActualState() == ENEMY_STATE_ALIVE)
                    {
                        std::cout<<"Ya lo tengo"<<std::endl;
                        m_target = i;
                        std::cout<<"Ahora el target es: "<<m_enemy[i]->GetID()<<std::endl;
                        m_is_attacking = true;
                    }
                }
            }
        
        }
    }
    
     void Ataque::Attack()
    {
        if(m_is_attacking)
        {
            if(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x < m_rango && m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y < m_rango && 
                   m_enemy[m_target]->GetPosition().x - m_mainSprite.getPosition().x < m_rango && m_enemy[m_target]->GetPosition().y-m_mainSprite.getPosition().y < m_rango)
            {
                float angle=0;
                float hipotenusa;
                float PI= 3.14159265;
                float incremento_x,incremento_y;
                sf::Vector2f m_direccion_sentido;
                hipotenusa=sqrt(pow(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x,2)+pow(m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y,2));
                angle = asin (abs(m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y)/hipotenusa) * 180.0 / PI;
                angle=angle-90;
                
               if(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x<0 &&  m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y>0){//primer cuadrante
                  
               angle=angle*-1;
               
               m_direccion_sentido.x=(m_enemy[m_target]->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y= m_enemy[m_target]->GetPosition().y- m_mainSprite.getPosition().y;

               }
               if(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x>0 &&  m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y<0){// tercer cuadrante

               angle=180-angle;
               m_direccion_sentido.x=(m_enemy[m_target]->GetPosition().x - m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y=m_enemy[m_target]->GetPosition().y - m_mainSprite.getPosition().y;
               }

               if(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x<=0 &&  m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y<=0){ //cuarto cuadrante

               angle=angle-180;
               m_direccion_sentido.x=(m_enemy[m_target]->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y=m_enemy[m_target]->GetPosition().y - m_mainSprite.getPosition().y;
               }
                
               if(m_mainSprite.getPosition().x-m_enemy[m_target]->GetPosition().x>0 &&  m_mainSprite.getPosition().y-m_enemy[m_target]->GetPosition().y>0){ //cuarto cuadrante

               m_direccion_sentido.x=(m_enemy[m_target]->GetPosition().x- m_mainSprite.getPosition().x)*-1;
               m_direccion_sentido.y=(m_enemy[m_target]->GetPosition().y- m_mainSprite.getPosition().y);
               }
                m_mainSprite.setRotation(angle);
           //     m_bullet->Shoot(angle,incremento_x,incremento_y);
                
                if(m_refresco==0)
                {                
                    if(shoot_time.getElapsedTime().asSeconds() > m_cadencia )
                    {
                        Bala * c_bala= new Bala(m_datos,m_mainSprite.getPosition(),m_direccion_sentido,angle);
                        m_bala.push_back(c_bala);
                        shoot_time.restart();
                    }
                }
                else
                {
                    if(refresh_time.getElapsedTime().asSeconds() < m_refresco)
                    {
                        if(shoot_time.getElapsedTime().asSeconds() > m_cadencia )
                        {
                            Bala * c_bala= new Bala(m_datos,m_mainSprite.getPosition(),m_direccion_sentido,angle);
                            m_bala.push_back(c_bala);
                            shoot_time.restart();
                            wait_time.restart();
                        }
                    }
                    else
                    {
                        if(wait_time.getElapsedTime().asSeconds() < TIEMPO_ESPERA)
                        {
                            std::cout<<"ESTOY RECARGANDO!!"<<std::endl;
                            
                        }
                        else
                            refresh_time.restart();
                        
                    }
                
                }
                

            }
            else
            {
                std::cout<<"Dejo de atacar"<<std::endl;
                m_mainSprite.setRotation(0);
                m_is_attacking = false;
            }

        }
        else
        {
            std::cout<<"Dejo de atacar"<<std::endl;
            m_mainSprite.setRotation(0);
            m_is_attacking = false;
        }
    }
     
    bool Ataque::CheckColision()
    {
        for(int i = 0; i<m_bala.size(); i++)
        {
            for(int j=0; j<m_enemy.size(); j++)
            {
                if(m_bala[i]->GetSprite().getGlobalBounds().intersects(m_enemy[j]->GetSprite().getGlobalBounds()))
                {
                    delete m_bala[i];
                    m_bala.erase(m_bala.begin() + i);
                    m_enemy.at(j)->TakeDamage(m_potencia);
                    if(m_enemy[j]->GetActualState() == ENEMY_STATE_DEAD )
                    {
                        m_enemy[j]->SetKiller(m_id);
                        std::cout<<"Enemigo muerto, mi id es "<< m_id << std::endl;
                        m_mainSprite.setRotation(0);
                        m_is_attacking = false;
                        m_target = -1;
                    }
                }
            }
        }
    }
    
    int Ataque::CalculateRec(int l_sum)
    {   
        float porcentaje = m_porcentaje/100.0;
        std::cout<<porcentaje<<std::endl;
        std::cout<<m_precio<<std::endl;
        std::cout<<m_precio * porcentaje<<std::endl;
        int resultado = l_sum + (m_precio * porcentaje);
        std::cout<<"Entro y me sale un total de"<<resultado<<std::endl;
        return resultado;
    }
}