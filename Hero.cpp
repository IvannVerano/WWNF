#include "Hero.hpp"
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"
#include <iostream>


namespace Zenon {

    Hero::Hero(GameDataRef l_data, Maps &l_map, int l_id) : m_data(l_data), m_map(l_map) {
        m_Id = l_id;
        m_state = HERO_IDLE_STATE;
        m_direction = sf::Vector2f(-1, -1);

        m_destinyPointer.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_destinyPointer.setTextureRect(sf::IntRect(0, 0, 65, 64));
        m_destinyPointer.scale(0.5, 0.5);
        m_destinyPointer.setOrigin(m_destinyPointer.getLocalBounds().width / 2, m_destinyPointer.getLocalBounds().height / 2);


        m_heroArrow.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_heroArrow.setTextureRect(sf::IntRect(68, 44, 24, 20));
        m_heroArrow.setOrigin(m_heroArrow.getGlobalBounds().width / 2, m_heroArrow.getGlobalBounds().height / 2);
        m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y - 60);

        m_heroPlace.setTexture(m_data->assets.GetTexture("Hero_GUI"));
        m_heroPlace.setTextureRect(sf::IntRect(122, 0, 68, 64));
        m_heroPlace.setOrigin(m_heroPlace.getGlobalBounds().width / 2, m_heroPlace.getGlobalBounds().height / 2);
        m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y + 30);
        
        m_isSelected = false;
        m_waypoint = 1;
        m_pathComplete = false;
    }

    void Hero::Update(float dt) {
        if (m_live <= 0) {
            m_state = HERO_DEAD_STATE;
        }

        if (m_state != HERO_DEAD_STATE) {
            m_heroArrow.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y - 60);
            m_heroPlace.setPosition(m_mainSprite.getPosition().x, m_mainSprite.getPosition().y + 30);
            m_destinyPointer.rotate(2);
            if (m_mainSprite.getGlobalBounds().contains(m_destinyPointer.getPosition()))
                m_state = HERO_IDLE_STATE;
            if (m_state == HERO_MOVING_STATE) {
                if (!m_pathComplete) {
                    sf::Vector2f distance = m_path[m_waypoint] - m_mainSprite.getPosition();
                    float module_distance = Module(distance);
                    if (module_distance <= HERO_DETECT_WAYPOINT) {
                        if (m_waypoint < m_path.size() - 1) {
                            m_waypoint++;
                            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
                            m_direction = Normalize(m_direction, Module(m_direction));
                        } else {
                            m_pathComplete = true;
                            m_direction = m_destiny - m_mainSprite.getPosition();
                            m_direction = Normalize(m_direction, Module(m_direction));
                        }
                    }

                }

                this->Move(dt);
            }
            
                        if(m_doping!=false)
            {
                    if(m_time.getElapsedTime().asSeconds()>TIEMPO_ADRENALINA && m_doping==true){                       
                        m_doping=false;
                        m_power=m_initpower;
                        m_time.restart();
                    }
                    else
                    {
                        std::cout<<"CHACHO QUE VOY CICLAO!!(clase hero)"<<std::endl;
                        m_power=m_initpower*EFECTO_ADRENALINA;
                    }   
            } 
        }
    }
    
    void Hero::ResizeLife()
    {
        float result;
        result = (m_live*100)/m_initlive;
        m_heroHUDLife.setSize(sf::Vector2f(result,15));
    }

    void Hero::OrderMovement(sf::Vector2f l_destiny) {
        m_backupPath = m_path;
        m_path.clear();
        if (m_map.GetPath(m_mainSprite.getPosition(), l_destiny, m_path)) 
        { 
            m_waypoint = 1;
            m_pathComplete = false;
            std::cout<<"Entro"<<std::endl;
            this->CheckPath();
            std::reverse(std::begin(m_path), std::end(m_path));
            m_destiny = l_destiny;
            m_destinyPointer.setPosition(l_destiny);
            m_direction = m_path[m_waypoint] - m_mainSprite.getPosition();
            m_direction = Normalize(m_direction, Module(m_direction));
            m_state = HERO_MOVING_STATE;
        } 
        else 
        {
            m_path = m_backupPath;
        }
    }

    void Hero::Move(float dt) {
        if(m_doping!=true){
            m_mainSprite.move(dt * m_direction.x*HERO_SPEED, dt * m_direction.y * HERO_SPEED);

        }else{
            m_mainSprite.move((dt * m_direction.x*HERO_SPEED)*EFECTO_ADRENALINA, (dt * m_direction.y * HERO_SPEED)*EFECTO_ADRENALINA);

        }
    };

    void Hero::TakeDamage(float l_damage) {
        m_live -= l_damage;
        this->ResizeLife();
        if (m_live <= 0.0f) {
            m_state = HERO_DEAD_STATE;
        }
    }

    void Hero::Draw() {
        if (m_state == HERO_MOVING_STATE) {
            m_data->window.draw(m_destinyPointer);
        }
        if (m_isSelected) 
        {
            m_data->window.draw(m_heroPlace);
            m_data->window.draw(m_heroArrow);
        }
        m_data->window.draw(m_heroHUD);
        m_data->window.draw(m_heroHUDred);
        m_data->window.draw(m_heroHUDLife);
        m_data->window.draw(m_mainSprite);
    }

    bool Hero::IsSelected() {
        return m_isSelected;
    }

    bool Hero::IsClicked() {
        return m_data->input.IsSpriteClicked(m_mainSprite, sf::Mouse::Left, m_data->window);
    }

    void Hero::Select() {
        m_isSelected = true;
    }

    void Hero::CheckPath() {
        int contador = 0;
        while (contador < m_path.size()) {
            if (contador + 1 >= m_path.size() || contador - 1 == 0)
                contador++;
            else {
                if ((m_path[contador - 1].y == m_path[contador].y) && (m_path[contador + 1].x == m_path[contador].x)) {
                    m_path.erase(m_path.begin() + contador);
                } else
                    contador++;
            }
        }
    }
    
    void Hero::Heal(float l_heal)
    {
            if(m_live < m_initlive)
            {
                m_live+=l_heal;
                this->ResizeLife();
            }
    }

    int Hero::GetId() {
        return m_Id;
    }

    sf::FloatRect Hero::GetGB() {
        return m_mainSprite.getGlobalBounds();
    }

    sf::Vector2f Hero::GetCurrentPosition() {
        return m_mainSprite.getPosition();
    }

    float Hero::GetLive() {
        return m_live;
    }

    int Hero::GetState() {
        return m_state;
    }
    
    void Hero::Deselect()
    {
        m_isSelected = false;
    }
    
    bool Hero::IsRecovered()
    {
        if(m_live == m_initlive)
            return true;
        return false;
    }
    
    bool Hero::ImTargeted()
    {
        return m_data->input.IsSpriteClicked(m_mainSprite, sf::Mouse::Right, m_data->window);
    }
        void Hero::SetDoping(bool l_doping) {

        m_doping=l_doping;
    }    
    

}