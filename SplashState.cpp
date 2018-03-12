
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {


    }

    void SplashState::Init() {


    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->_data->window.close();
            }
        }

    }

    void SplashState::Update(float dt) {



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

        std::vector<sf::Vector2f> m_pointsV = CalculateBQ(sf::Vector2f(this->_data->window.getSize().x / 2 - 300, 300),
                sf::Vector2f(this->_data->window.getSize().x / 2 + 300, 300),
                sf::Vector2f(this->_data->window.getSize().x / 2 - 150, 100),
                sf::Vector2f(this->_data->window.getSize().x / 2 + 150, 500),
                20
                );

        sf::VertexArray vertices = ToVertex(m_pointsV);

        this->_data->window.draw(vertices);


        this->_data->window.display();
    }
}

