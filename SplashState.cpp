
#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Zenon {

    SplashState::SplashState(GameDataRef data) : _data(data) {


    }

    void SplashState::Init() {

        /*  m_path.m_points = {
              {200, 200},
              {300, 200},
              {400, 200},
              {500, 200}
          };

          for (int i = 0; i < m_path.m_points.size(); i++) {
              sf::CircleShape circle;
              circle.setRadius(8);
              circle.setFillColor(sf::Color::Yellow);
              circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
              circle.setPosition(m_path.m_points[i].x, m_path.m_points[i].y);
              m_circles.push_back(circle);
          }
         */
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while (this->_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                this->_data->window.close();
            }
            /*
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                            m_cambio = true;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            m_isMoving = true;
                            m_circleDirH = -1;
                            m_circleDirV = 0;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            m_isMoving = true;
                            m_circleDirH = 1;
                            m_circleDirV = 0;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            m_isMoving = true;
                            m_circleDirH = 0;
                            m_circleDirV = 1;
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            m_isMoving = true;
                            m_circleDirH = 0;
                            m_circleDirV = -1;

                        }
             */
        }

    }

    void SplashState::Update(float dt) {

        /*for (float t = 0.0f; t < (float) m_path.m_points.size(); t += 0.05f) {
            Point2D pos = m_path.GetSplinePoint(t, false);
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(3.0f, 3.0f));
            rect.setOrigin(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2);
            rect.setPosition(pos.x, pos.y);
            m_pathShape.push_back(rect);
        }


        for (int i = 0; i < m_circles.size(); i++) {
            m_circles[i].setFillColor(sf::Color::Yellow);
        }

        if (m_cambio) {

            m_selectedPoint++;

            if (m_selectedPoint >= m_path.m_points.size()) {
                m_selectedPoint = 0;
            }

            m_cambio = false;
        }

        if (m_isMoving) {
            m_circles[m_selectedPoint].move(CIRCLE_SPEED * dt * m_circleDirH, CIRCLE_SPEED * dt * m_circleDirV);
            m_isMoving = false;
        }

        m_circles[m_selectedPoint].setFillColor(sf::Color::Red);
         */


    }

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

    sf::VertexArray SplashState::ToVertex(std::vector<sf::Vector2f> l_points) {
        sf::VertexArray vertices(sf::LinesStrip, 0);

        // Append the points as vertices to the vertex array
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

        /*
        for (int i = 0; i < m_circles.size(); i++) {
            this->_data->window.draw(m_circles[i]);
        }

        for (int i = 0; i < m_pathShape.size(); i++) {
            this->_data->window.draw(m_pathShape[i]);
        }

         */


        this->_data->window.display();
    }
}

