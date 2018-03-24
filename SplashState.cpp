
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {

    }

    void SplashState::Init() {


        LoadPaths();
        LoadAssets();

    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->_data->window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                m_wantsNew = true;
            }
        }
    }

    void SplashState::Update(float dt) {

        if (m_wantsNew) {
            SpawnEnemy(sf::Vector2f(50, 50), 0);
            m_wantsNew = false;
        }

        for (int i = 0; i < m_enemyVector.size(); i++) {
            m_enemyVector[i]->Update(dt);

            if (m_enemyVector[i]->GetGB().intersects(m_point1.getGlobalBounds()) ||
                    m_enemyVector[i]->GetGB().intersects(m_point2.getGlobalBounds()) ||
                    m_enemyVector[i]->GetGB().intersects(m_point3.getGlobalBounds())) {
                delete m_enemyVector[i];
                m_enemyVector.erase(m_enemyVector.begin() + i);
            }
        }

    }

    void SplashState::LoadAssets() {

        _data->assets.LoadTexture("Point1 Texture", POINT1_TEXTURE);
        _data->assets.LoadTexture("Point2 Texture", POINT2_TEXTURE);
        _data->assets.LoadTexture("Enemy Texture", ENEMY_TEXTURE);
        _data->assets.LoadTexture("Spawn Texture", SPAWN_TEXTURE);

        m_point1.setTexture(_data->assets.GetTexture("Point1 Texture"));
        m_point2.setTexture(_data->assets.GetTexture("Point2 Texture"));
        m_point3.setTexture(_data->assets.GetTexture("Point2 Texture"));
        m_spawn.setTexture(_data->assets.GetTexture("Spawn Texture"));

        m_point1.setOrigin(m_point1.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_point2.setOrigin(m_point2.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_point3.setOrigin(m_point2.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_spawn.setOrigin(m_spawn.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);

        m_point1.setScale(0.5, 0.5);
        m_point2.setScale(0.5, 0.5);
        m_point3.scale(0.5, 0.5);
        m_spawn.scale(0.3, 0.3);

        m_point1.setPosition(m_caminos[0].m_bRoutes[2].m_endPoint);
        m_point2.setPosition(m_caminos[0].m_bRoutes[0].m_endPoint);
        m_point3.setPosition(m_caminos[0].m_bRoutes[1].m_endPoint);
        m_spawn.setPosition(m_caminos[0].m_startPoint);

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


        m_caminos.push_back(t_bezier);

        for (int i = 0; i < m_caminos[0].m_bezierBody.size(); i++) {
            sf::CircleShape circle;
            circle.setRadius(5.0f);
            circle.setFillColor(sf::Color::Red);
            circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
            circle.setPosition(m_caminos[0].m_bezierBody[i].x, m_caminos[0].m_bezierBody[i].y);
            m_wps.push_back(circle);
            for (int j = 0; j < m_caminos[0].m_bRoutes.size(); j++) {
                for (int k = 0; k < m_caminos[0].m_bRoutes[j].m_bezierBody.size(); k++) {
                    sf::CircleShape circle;
                    circle.setRadius(5.0f);
                    circle.setFillColor(sf::Color::Red);
                    circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
                    circle.setPosition(m_caminos[0].m_bRoutes[j].m_bezierBody[k].x, m_caminos[0].m_bRoutes[j].m_bezierBody[k].y);
                    m_wps.push_back(circle);
                }
            }

        }

        for (int i = 0; i < m_caminos.size(); i++) {
            m_pathsVertex.push_back(ToVertex(m_caminos[i].m_bezierBody));
            for (int j = 0; j < m_caminos[i].m_bRoutes.size(); j++) {
                m_pathsVertex.push_back(ToVertex(m_caminos[i].m_bRoutes[j].m_bezierBody));
            }
        }

    }

    void SplashState::SpawnEnemy(sf::Vector2f l_position, int l_path) {
        const std::vector<Enemy*>& l_neighbor = m_enemyVector;
        const std::vector<Bezier>& l_routes = m_caminos;
        m_enemy = new Enemy(_data, l_position, l_neighbor, l_routes, l_path);
        m_enemyVector.push_back(m_enemy);
    }

    sf::VertexArray SplashState::ToVertex(std::vector<sf::Vector2f> l_points) {
        sf::VertexArray vertices(sf::LinesStrip, 0);

        for (std::vector<sf::Vector2f>::const_iterator a = l_points.begin(); a != l_points.end(); ++a)
            vertices.append(sf::Vertex(*a, sf::Color::White));

        return vertices;
    }

    void SplashState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);

        this->_data->window.draw(this->_background);

        for (int i = 0; i < m_pathsVertex.size(); i++) {
            this->_data->window.draw(m_pathsVertex[i]);
        }

        this->_data->window.draw(m_point1);
        this->_data->window.draw(m_point2);
        this->_data->window.draw(m_point3);
        this->_data->window.draw(m_spawn);

        for (int j = 0; j < m_wps.size(); j++) {
            this->_data->window.draw(m_wps[j]);
        }

        for (int i = 0; i < m_enemyVector.size(); i++) {
            m_enemyVector[i]->Draw();
        }

        this->_data->window.display();
    }
}

