
#include <sstream>
#include "SplashState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "Trampa.hpp"
#include "Attack.hpp"
#include "Defensa.hpp"
#include "HUD.hpp"
#include "Hero.hpp"
#include <string>
#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data, std::vector<FichaTrampa*> l_fichaTrampa, int l_dinero) : m_data(data) {
        m_trampasSel = l_fichaTrampa;
        m_disponible = l_dinero;
    }

    void SplashState::Init() {
        std::cout << "Tienes " << m_trampasSel.size() << " trampas" << std::endl;

        const char * titulo = "definitivo12.tmx";
        map = new Maps(m_data, titulo);

        m_loc_placers = map->GetPlacerLocation();
        //Creamos los placer en base a nuestro mapa de polla
        for (int x = 0; x < m_loc_placers.size(); x++) {
            Placer* plaser = new Placer(m_data, m_loc_placers.at(x));
            m_placer.push_back(plaser);
        }

        m_trampa = -1;
        
        Maps &mapref = *map;
        m_hero = new Hero(m_data, mapref);

        m_hud = new HUD(m_data, m_trampasSel);
        m_noCompruebes = false;

        m_mouseConstruct.setTexture(m_data->assets.GetTexture("CURSOR_BUILD"));
        m_mouseConstruct.setOrigin(m_mouseConstruct.getGlobalBounds().width / 2, m_mouseConstruct.getGlobalBounds().height / 2);
        m_mouseConstruct.scale(0.7, 0.7);


        LoadPaths();

        m_point1.setTexture(this->m_data->assets.GetTexture("point1"));
        m_point1.setOrigin(m_point1.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_point1.scale(0.5, 0.5);
        m_point1.setPosition(m_routes[0].m_bRoutes[0].m_endPoint.x, m_routes[0].m_bRoutes[0].m_endPoint.y);

        m_point2.setTexture(this->m_data->assets.GetTexture("point1"));
        m_point2.setOrigin(m_point2.getGlobalBounds().width / 2, m_point2.getGlobalBounds().height / 2);
        m_point2.scale(0.5, 0.5);
        m_point2.setPosition(m_routes[0].m_bRoutes[1].m_endPoint.x, m_routes[0].m_bRoutes[1].m_endPoint.y);

        m_point3.setTexture(this->m_data->assets.GetTexture("tienda"));
        m_point3.setOrigin(m_point3.getGlobalBounds().width / 2, m_point3.getGlobalBounds().height / 2);
        m_point3.scale(0.5, 0.5);
        m_point3.setPosition(m_routes[0].m_bRoutes[2].m_endPoint.x, m_routes[0].m_bRoutes[2].m_endPoint.y);

        //SpawnEnemy(sf::Vector2f(m_routes[0].m_startPoint.x, m_routes[0].m_startPoint.y), 0);

        m_textoDinero.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_textoDinero.setString(std::to_string(m_disponible));
        m_textoDinero.setCharacterSize(20);
        m_textoDinero.setOrigin(m_textoDinero.getGlobalBounds().width / 2, m_textoDinero.getGlobalBounds().height / 2);
        m_textoDinero.setPosition(900, 800);


    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->m_data->window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (m_hud->CheckClick()) {
                    m_trampa = m_hud->GetClick();
                }
                for (int i = 0; i < m_placer.size(); i++) {
                    if (m_placer.at(i)->Clicked(m_trampa)) {
                        if (m_trampa> -1) {
                            if (m_trampasSel.at(m_trampa)->GetTipo() == 1) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Enemy*> &enes = m_enemies;
                                    const std::vector<Bala*> &bull = m_bullets;
                                    Trampa* tramp = new Attack(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes, m_bullets);
                                    tramp->SetAttributes(m_trampas.size(), m_trampasSel[m_trampa]->GetCadencia(), m_trampasSel[m_trampa]->GetAparicion(), m_trampasSel[m_trampa]->GetPotencia(), m_trampasSel[m_trampa]->GetRango(), m_trampasSel[m_trampa]->GetRefresco(), 0, m_trampasSel[m_trampa]->GetPorcentaje(), m_trampasSel[m_trampa]->GetPrecio());
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                }
                                else
                                {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            } 
                            else if (m_trampasSel.at(m_trampa)->GetTipo() == 2) {
                                if (m_trampasSel.at(m_trampa)->Afordable(m_disponible)) {
                                    const std::vector<Enemigo*> &enes = m_enemys;
                                    Trampa* tramp = new Defensa(m_data, m_placer.at(i)->GetPosicion(), m_trampasSel.at(m_trampa)->GetTexturaPosicion(), enes, RANGO_TORRE_DEFENSA);
                                    m_trampas.push_back(tramp);
                                    m_disponible -= m_trampasSel.at(m_trampa)->GetPrecio();
                                }
                                else
                                {
                                    m_placer.at(i)->SetOcupadoFalse();
                                }
                            }
                        }
                    }
                }
                if(m_hero->IsClicked())
                {
                   m_hero->Select();
                   std::cout<<"Me seleccionas"<<std::endl;
                }
                else
                {
                   if(m_hero->IsSelected())
                   {
                      m_hero->OrderMovement((sf::Vector2f)m_data->input.GetMousePosition(m_data->window));
                      std::cout<<"Me ordenas moverme"<<std::endl;
                   }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                m_trampa = 1;
                std::cout << "Cambio a metralletas" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                m_trampa = 2;
                std::cout << "Cambio a Defensa" << std::endl;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                m_wantsNew = true;
            }
        }
    }

    void SplashState::Update(float dt) {

        if (m_wantsNew) {
            SpawnEnemy2(sf::Vector2f(m_routes[0].m_startPoint.x, m_routes[0].m_startPoint.y), 0);
            m_wantsNew = false;
        }
        
        m_hero->Update(dt);

        m_textoDinero.setString(std::to_string(m_disponible));
        int counter = 0;
        for (int i = 0; i < m_trampas.size(); i++) {
            m_trampas.at(i)->Update(dt);
        }
        for (int i = 0; i < m_enemys.size(); i++) {
            m_enemys.at(i)->Update(dt);
        }
        
        for(int i=0; i<m_bullets.size(); i++)
        {
            m_bullets[i]->Update(dt);
        }

        for (int i = 0; i < m_enemies.size(); i++) {
            if (m_enemies.at(i)->GetActualState() != ENEMY_STATE_DEAD) {
                m_enemies.at(i)->Update(dt);
                if (m_enemies[i]->GetGB().intersects(m_point1.getGlobalBounds()) ||
                        m_enemies[i]->GetGB().intersects(m_point2.getGlobalBounds()) ||
                        m_enemies[i]->GetGB().intersects(m_point3.getGlobalBounds())) {
                    for (int x = 0; x < m_trampas.size(); x++) 
                    {
                        m_trampas[x]->DeleteTarget(i);
                    }
                    delete m_enemies[i];
                    m_enemies.erase(m_enemies.begin() + i);
                }
            }

        }
        
        this->CheckColision();

        for (int i = 0; i < m_placer.size(); i++) {
            if (m_placer.at(i)->Hovered() && !m_placer.at(i)->GetOccuped()) {
                counter++;
            }
        }

        if (counter > 0)
            m_hideCursor = true;
        else
            m_hideCursor = false;

        m_mouseConstruct.setPosition((sf::Vector2f)m_data->input.GetMousePosition(m_data->window));

    }

    void SplashState::LoadPaths() {

        Bezier t_bezier;
        t_bezier.probability = 50;
        t_bezier.m_startPoint = sf::Vector2f(50, 50);
        t_bezier.m_endPoint = sf::Vector2f(725, 525);
        t_bezier.m_controlPoint1 = sf::Vector2f(500, 100);
        t_bezier.m_controlPoint2 = sf::Vector2f(500, 500);
        t_bezier.m_segments = 20;
        t_bezier.m_bPoints[100] = t_bezier.m_endPoint;
        t_bezier.create();
        t_bezier.m_bPoints[10] = t_bezier.m_bezierBody[10];
        t_bezier.m_bPoints[20] = t_bezier.m_bezierBody[20];

        Bezier t_bezier2;
        t_bezier2.probability = 60;
        t_bezier2.m_startPoint = t_bezier.m_bPoints[10];
        t_bezier2.m_endPoint = sf::Vector2f(750, 100);
        t_bezier2.m_controlPoint1 = sf::Vector2f(500, 200);
        t_bezier2.m_controlPoint2 = sf::Vector2f(500, 100);
        t_bezier2.m_segments = 20;
        t_bezier2.create();

        t_bezier.m_bRoutes.push_back(t_bezier2);

        Bezier t_bezier3;
        t_bezier3.probability = 30;
        t_bezier3.m_startPoint = t_bezier.m_bPoints[10];
        t_bezier3.m_endPoint = sf::Vector2f(450, 550);
        t_bezier3.m_controlPoint1 = sf::Vector2f(350, 400);
        t_bezier3.m_controlPoint2 = sf::Vector2f(300, 500);
        t_bezier3.m_segments = 20;
        t_bezier3.create();

        t_bezier.m_bRoutes.push_back(t_bezier3);

        Bezier t_bezier4;
        t_bezier4.probability = 100;
        t_bezier4.m_startPoint = t_bezier.m_bPoints[20];
        t_bezier4.m_endPoint = sf::Vector2f(1100, 200);
        t_bezier4.m_controlPoint1 = sf::Vector2f(1100, 400);
        t_bezier4.m_controlPoint2 = sf::Vector2f(1100, 500);
        t_bezier4.m_segments = 20;
        t_bezier4.create();

        t_bezier.m_bRoutes.push_back(t_bezier4);


        m_routes.push_back(t_bezier);

        for (int i = 0; i < m_routes[0].m_bezierBody.size(); i++) {
            sf::CircleShape circle;
            circle.setRadius(5.0f);
            circle.setFillColor(sf::Color::Red);
            circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
            circle.setPosition(m_routes[0].m_bezierBody[i].x, m_routes[0].m_bezierBody[i].y);
            m_wps.push_back(circle);
            for (int j = 0; j < m_routes[0].m_bRoutes.size(); j++) {
                for (int k = 0; k < m_routes[0].m_bRoutes[j].m_bezierBody.size(); k++) {
                    sf::CircleShape circle;
                    circle.setRadius(5.0f);
                    circle.setFillColor(sf::Color::Red);
                    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
                    circle.setPosition(m_routes[0].m_bRoutes[j].m_bezierBody[k].x, m_routes[0].m_bRoutes[j].m_bezierBody[k].y);
                    m_wps.push_back(circle);
                }
            }

        }

        for (int i = 0; i < m_routes.size(); i++) {
            m_pathsVertex.push_back(ToVertex(m_routes[i].m_bezierBody));
            for (int j = 0; j < m_routes[i].m_bRoutes.size(); j++) {
                m_pathsVertex.push_back(ToVertex(m_routes[i].m_bRoutes[j].m_bezierBody));
            }
        }
    }

    void SplashState::SpawnEnemy(sf::Vector2f l_position, int l_path) {
        const std::vector<Enemigo*>& l_neighbor = m_enemys;
        const std::vector<Bezier>& l_routes = m_routes;
        m_enemy = new Enemigo(m_data, l_position, l_neighbor, l_routes, l_path);
        m_enemys.push_back(m_enemy);
    }

    void SplashState::SpawnEnemy2(sf::Vector2f l_position, int l_path) {
        const std::vector<Enemy*>& l_neighbor = m_enemies;
        const std::vector<Bezier>& l_routes = m_routes;
        m_ENEMY = new Enemy(m_data, l_position, l_neighbor, l_routes, l_path);
        m_enemies.push_back(m_ENEMY);
    }

    sf::VertexArray SplashState::ToVertex(std::vector<sf::Vector2f> l_points) {
        sf::VertexArray vertices(sf::LinesStrip, 0);

        for (std::vector<sf::Vector2f>::const_iterator a = l_points.begin(); a != l_points.end(); ++a)
            vertices.append(sf::Vertex(*a, sf::Color::White));

        return vertices;
    }

    void SplashState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.draw(m_textoDinero);
        map->Draw();
        this->m_data->window.draw(this->_background);


        for (int i = 0; i < m_placer.size(); i++) {
            m_placer.at(i)->Draw();
        }

        for (int i = 0; i < m_pathsVertex.size(); i++) {
            this->m_data->window.draw(m_pathsVertex[i]);
        }

        for (int i = 0; i < m_wps.size(); i++) {
            this->m_data->window.draw(m_wps[i]);
        }

        this->m_data->window.draw(m_point1);
        this->m_data->window.draw(m_point2);
        this->m_data->window.draw(m_point3);

        for (int i = 0; i < m_trampas.size(); i++) {
            m_trampas.at(i)->Draw();
        }

        for (int i = 0; i < m_enemys.size(); i++) {
            m_enemys.at(i)->Draw();
        }

        for (int i = 0; i < m_enemies.size(); i++) {
            m_enemies.at(i)->Draw();
        }
        
        for(int i = 0; i< m_bullets.size(); i++)
        {
            m_bullets[i]->Draw();
        }

        m_hud->Draw();
        m_hero->Draw();

        if (m_hideCursor) {
            this->m_data->window.setMouseCursorVisible(false);
            this->m_data->window.draw(m_mouseConstruct);
        } else
            this->m_data->window.setMouseCursorVisible(true);

        this->m_data->window.display();
    }
    
    void SplashState::CheckColision()
    {
        for(int i=0; i<m_enemies.size(); i++)
        {
            for(int j=0; j<m_bullets.size(); j++)
            {
                
                if(m_enemies[i]->GetSprite().getGlobalBounds().intersects(m_bullets[j]->GetSprite().getGlobalBounds()))
                {
                    int killerCandidate = m_bullets[j]->WhoShooted();
                    delete m_bullets[j];
                    m_bullets.erase(m_bullets.begin()+j);
                    m_enemies[i]->TakeDamage(m_bullets[j]->GetPower());
                    if(m_enemies[i]->GetActualState()==ENEMY_STATE_DEAD)
                    {
                        for(int w=0; w<m_trampas.size(); w++)
                        {
                            m_trampas[w]->DeleteTarget(i);
                        }
                        m_disponible = m_trampas[killerCandidate]->CalculateRec(m_disponible);
                        delete m_enemies[i];
                        m_enemies.erase(m_enemies.begin() + i);
                    }
                }
                 
            }
        }
    }
}

