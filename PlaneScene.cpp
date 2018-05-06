#include "PlaneScene.hpp"
#include "SplashState.hpp"

namespace Zenon
{
    PlaneScene::PlaneScene(GameDataRef l_data, std::vector<FichaTrampa*> l_fichaTrampa): m_data(l_data)
    {
        m_fichaTrampa = l_fichaTrampa;
        m_destinyPoint = m_data->reward.GetLevelLocation();
    }
    
    void PlaneScene::Init()
    {
        m_plane.setTexture(m_data->assets.GetTexture("Plane"));
        m_plane.setOrigin(m_plane.getGlobalBounds().width/2, m_plane.getGlobalBounds().height/2);
        m_destiny.setTexture(m_data->assets.GetTexture("MapMarker"));
        m_destiny.setOrigin(m_destiny.getGlobalBounds().width/2, m_destiny.getGlobalBounds().height/2);
        m_background.setTexture(m_data->assets.GetTexture("CleanMap"));
        m_nextButton.setTexture(m_data->assets.GetTexture("Desplegar"));
        m_nextButton.setOrigin(m_nextButton.getGlobalBounds().width/2, m_nextButton.getGlobalBounds().height/2);
        
        
        m_destiny.setPosition(m_destinyPoint);
        m_nextButton.setPosition(m_destinyPoint.x + 100, m_destinyPoint.y + 50);
       
        m_plane.setPosition(100, 800);
        
        m_nextButton.scale(0.3,0.3);
        m_destiny.scale(0.8,0.8);
        m_plane.scale(0.2,0.2); 
        
        m_trajectory = m_destinyPoint - m_plane.getPosition();
        
        m_camera.setCenter(m_plane.getPosition());
        m_camera.setSize(1920, 1080);
        m_camera.zoom(0.5f);
        
        float module = Module(m_trajectory);
        m_normalized = Normalize(m_trajectory, module);
        
        this->SetPlaneRotation();
        
    }
    
    void PlaneScene::HandleInput()
    {
        sf::Event event;
        while (this->m_data->window.pollEvent(event)) 
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i click = sf::Mouse::getPosition(m_data->window);
                sf::Vector2f worldPos = m_data->window.mapPixelToCoords(click);
                if (m_nextButton.getGlobalBounds().contains(worldPos)) 
                {
                    this->StartGame();
                }
            }
        }
    }
    
    void PlaneScene::Update(float dt)
    {
        m_destiny.rotate(20*dt);
        if(!hasArrived)
        {
            m_plane.move(m_normalized.x*dt*PLANE_SPEED, m_normalized.y*dt*PLANE_SPEED);
            m_camera.setCenter(m_plane.getPosition());
        }
        if (m_plane.getGlobalBounds().intersects(m_destiny.getGlobalBounds()))
        {
            hasArrived = true;
        }
    }
    
    void PlaneScene::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.setView(m_camera);
        this->m_data->window.draw(m_background);
        this->m_data->window.draw(m_destiny);
        this->m_data->window.draw(m_plane);
        if(hasArrived)
        {
            this->m_data->window.draw(m_nextButton);
        }
        this->m_data->window.display();
    }
    
    void PlaneScene::StartGame()
    {
        this->m_data->machine.AddState(StateRef(new SplashState(m_data, m_fichaTrampa)));
    }
    
    void PlaneScene::SetPlaneRotation()
    {
                float angle = 0;
                float hipotenusa;
                hipotenusa = std::sqrt(std::pow(m_plane.getPosition().x - m_destinyPoint.x, 2) + std::pow(m_plane.getPosition().y - m_destinyPoint.y, 2));
                angle = std::asin(abs(m_plane.getPosition().y - m_destinyPoint.y) / hipotenusa) * 180.0 / PI;
                angle-=90;
        
                if (m_plane.getPosition().x - m_destinyPoint.x < 0 && m_plane.getPosition().y - m_destinyPoint.y > 0) {//primer cuadrante

                    angle = angle*-1;


                }
                if (m_plane.getPosition().x - m_destinyPoint.x > 0 && m_plane.getPosition().y - m_destinyPoint.y < 0) {// tercer cuadrante

                    angle = 180 - angle;
                }

                if (m_plane.getPosition().x - m_destinyPoint.x <= 0 && m_plane.getPosition().y - m_destinyPoint.y <= 0) { //cuarto cuadrante

                    angle = angle - 180;
                }
                
                m_plane.setRotation(angle);
    }
}