
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
            if (m_enemyVector[i]->GetCurrentWP() == m_caminos[0].m_bezierBody.size() - 1) {
                std::cout << "\n";
                std::cout << "[GAME OVER]: Un enemigo ha alcanzado el objetivo\n";
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
        m_spawn.setTexture(_data->assets.GetTexture("Spawn Texture"));

        m_point1.setOrigin(m_point1.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_point2.setOrigin(m_point2.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);
        m_spawn.setOrigin(m_spawn.getGlobalBounds().width / 2, m_point1.getGlobalBounds().height / 2);

        m_point1.scale(0.5, 0.5);
        m_point2.scale(0.5, 0.5);
        m_spawn.scale(0.3, 0.3);

        m_point1.setPosition(m_caminos[0].m_endPoint);
        m_point2.setPosition(m_caminos[0].m_bRoutes[0].m_endPoint);
        m_spawn.setPosition(m_caminos[0].m_startPoint);

    }

    void SplashState::LoadPaths() {

        Bezier t_bezier;
        t_bezier.probability = 80;
        t_bezier.m_startPoint = sf::Vector2f(50, 50);
        t_bezier.m_endPoint = sf::Vector2f(725, 525);
        t_bezier.m_controlPoint1 = sf::Vector2f(500, 100);
        t_bezier.m_controlPoint2 = sf::Vector2f(500, 500);
        t_bezier.m_segments = 20;
        t_bezier.m_bPoints[100] = t_bezier.m_endPoint;
        t_bezier.create(t_bezier.m_startPoint, t_bezier.m_endPoint, t_bezier.m_controlPoint1, t_bezier.m_controlPoint2, t_bezier.m_segments);
        t_bezier.m_bPoints[10] = t_bezier.m_bezierBody[10];

        Bezier t_bezier2;
        t_bezier2.probability = 20;
        t_bezier2.m_startPoint = t_bezier.m_bPoints[10];
        t_bezier2.m_endPoint = sf::Vector2f(750, 100);
        t_bezier2.m_controlPoint1 = sf::Vector2f(500, 200);
        t_bezier2.m_controlPoint2 = sf::Vector2f(500, 100);
        t_bezier2.m_segments = 20;
        t_bezier2.create(t_bezier2.m_startPoint, t_bezier2.m_endPoint, t_bezier2.m_controlPoint1, t_bezier2.m_controlPoint2, t_bezier2.m_segments);

        t_bezier.m_bRoutes.push_back(t_bezier2);

        m_caminos.push_back(t_bezier);

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
        this->_data->window.draw(m_spawn);

        for (int i = 0; i < m_enemyVector.size(); i++) {
            m_enemyVector[i]->Draw();
        }

        this->_data->window.display();
    }
}

