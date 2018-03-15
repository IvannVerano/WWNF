
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {


    }

    void SplashState::Init() {
        LoadAssets();
        LoadPaths();
        SpawnEnemy();
        LoadDestinies();
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->_data->window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                m_wantsNew = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                m_cambio = true;
            }
        }

    }

    void SplashState::Update(float dt) {


        if (m_wantsNew) {
            std::cout << "[SPAWN]: Spawn solicitado" << std::endl;
            std::cout << "\n";
            SpawnEnemy();
            m_wantsNew = false;
        }

        for (int i = 0; i < m_enemyVector.size(); i++) {
            if (m_enemyVector[i]->GetCurrentWP() == m_enemyVector[i]->GetPathEnd()) {
                std::cout << "[UPDATE]: Un enemigo ha alcanzado su objetivo --> Eliminamos" << std::endl;
                std::cout << "\n";
                delete m_enemyVector[i];
                m_enemyVector.erase(m_enemyVector.begin() + i);
            }
        }

        for (int i = 0; i < m_enemyVector.size(); i++) {
            if (m_cambio) {
                int r = rand() % m_enemyVector.size();
                std::cout << "[UPDATE] : Asignamos cambio de rama al enemigo: " << r << std::endl;
                std::cout << "\n";
                m_enemyVector[r]->SetCambio();
                m_cambio = false;
            }
            m_enemyVector[i]->Update(dt);
        }

    }

    void SplashState::LoadAssets() {
        this->_data->assets.LoadTexture("Enemy Texture", ENEMY_TEXTURE);
        this->_data->assets.LoadTexture("Objective Texture", OBJECTIVE_TEXTURE);
        this->_data->assets.LoadTexture("Objective2 Texture", OBJECTIVE2_TEXTURE);
        this->_data->assets.LoadTexture("Spawn Texture", SPAWN_TEXTURE);
    }

    void SplashState::LoadPaths() {
        m_pathPoints = CalculateBQ(sf::Vector2f(100, 50),
                sf::Vector2f(700, 500),
                sf::Vector2f(200, 100),
                sf::Vector2f(300, 550),
                20
                );

        m_caminos.push_back(m_pathPoints);

        std::vector<sf::Vector2f> temp = CalculateBQ(m_caminos[0][14],
                sf::Vector2f(700, 200),
                sf::Vector2f(300, 100),
                sf::Vector2f(500, 550),
                20
                );

        m_caminos.push_back(temp);

        m_pathVertex = ToVertex(m_pathPoints);
        m_pathVertex2 = ToVertex(temp);
    }

    void SplashState::SpawnEnemy() {
        const std::vector<Enemy*>& l_neighbors = m_enemyVector;
        m_enemy = new Enemy(_data, sf::Vector2f(m_caminos[0][0].x, m_caminos[0][0].y), l_neighbors);
        m_enemy->SetPath(m_caminos[0]);
        m_enemy->SetAlternative(m_caminos[1]);
        m_enemy->PutDiving();
        m_enemyVector.push_back(m_enemy);
    }

    void SplashState::LoadDestinies() {
        m_objective.setTexture(this->_data->assets.GetTexture("Objective Texture"));
        m_objective.setOrigin(m_objective.getGlobalBounds().width / 2, m_objective.getGlobalBounds().height / 2);
        m_objective.scale(0.6f, 0.6f);
        m_objective.setPosition(m_caminos[0][m_caminos[0].size() - 1].x, m_caminos[0][m_caminos[0].size() - 1].y);

        m_objective2.setTexture(this->_data->assets.GetTexture("Objective2 Texture"));
        m_objective2.setOrigin(m_objective2.getGlobalBounds().width / 2, m_objective2.getGlobalBounds().height / 2);
        m_objective2.scale(0.6f, 0.6f);
        m_objective2.setPosition(m_caminos[1][m_caminos[1].size() - 1].x, m_caminos[1][m_caminos[1].size() - 1].y);

        m_spawn.setTexture(this->_data->assets.GetTexture("Spawn Texture"));
        m_spawn.setOrigin(m_spawn.getGlobalBounds().width / 2, m_spawn.getGlobalBounds().height / 2);
        m_spawn.scale(0.3f, 0.3f);
        m_spawn.setPosition(m_caminos[0][0].x, m_caminos[0][0].y + 50);
    }

    //FUNCION QUE UTILIZAMOS PARA CALCULAR LOS PUNTOS DE LA CURVA BEZIER CUBICA
    //EN FUNCION DE EL INICIO, EL FIN Y DOS PUNTOS DE CONTROL

    std::vector<sf::Vector2f> SplashState::CalculateBQ
    (
            const sf::Vector2f &start,
            const sf::Vector2f &end,
            const sf::Vector2f &startControl,
            const sf::Vector2f &endControl,
            const std::size_t nSegments) {

        std::vector<sf::Vector2f> ret;

        if (!nSegments) {
            return ret;
        }

        ret.push_back(start);
        float p = 1.f / nSegments;
        float q = p;

        for (size_t i = 1; i < nSegments; i++, p += q) {
            ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) +
                    3.f * p * p * (start - 2.f * startControl + endControl) +
                    3.f * p * (startControl - start) + start);
        }

        ret.push_back(end);

        return ret;

    }

    //FUNCION AUXILIAR PARA CONVERTIR LOS VECTOR2F EN VETIRCES DIBUJABLES Y VISUALIZAR
    //LA CURVA

    sf::VertexArray SplashState::ToVertex(std::vector<sf::Vector2f> l_points) {
        sf::VertexArray vertices(sf::LinesStrip, 0);

        for (std::vector<sf::Vector2f>::const_iterator a = l_points.begin(); a != l_points.end(); ++a)
            vertices.append(sf::Vertex(*a, sf::Color::White));

        return vertices;
    }

    void SplashState::Draw(float dt) {
        this->_data->window.clear(sf::Color::Black);
        this->_data->window.draw(this->_background);
        this->_data->window.draw(m_spawn);
        this->_data->window.draw(m_pathVertex);
        this->_data->window.draw(m_pathVertex2);
        this->_data->window.draw(m_objective);
        this->_data->window.draw(m_objective2);
        for (int i = 0; i < m_enemyVector.size(); i++) {
            m_enemyVector[i]->Draw();
        }
        this->_data->window.display();
    }
}

