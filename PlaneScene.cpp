#include "PlaneScene.hpp"
#include "SplashState.hpp"

namespace Zenon
{
    PlaneScene::PlaneScene(GameDataRef l_data, std::vector<FichaTrampa*> l_fichaTrampa, sf::Music * l_theme): m_data(l_data)
    {
        m_theme = l_theme;
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
       
        m_plane.setPosition(960, 540);
        m_background.setOrigin(100, 800);
        m_background.scale(5.0,5.0);
        m_nextButton.scale(0.3,0.3);
        m_destiny.scale(0.8,0.8);
        
        
        m_trajectory = m_destinyPoint - m_plane.getPosition();
        
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
            m_background.move(m_normalized.x*dt*PLANE_SPEED * -1, m_normalized.y*dt*PLANE_SPEED *-1);
            m_destiny.move(m_normalized.x*dt*PLANE_SPEED * -1, m_normalized.y*dt*PLANE_SPEED *-1);
            m_nextButton.move(m_normalized.x*dt*PLANE_SPEED * -1, m_normalized.y*dt*PLANE_SPEED *-1);
        }
        if (m_plane.getGlobalBounds().intersects(m_destiny.getGlobalBounds()) && !hasArrived)
        {
            hasArrived = true;
            this->PlaySound();
        }
    }
    
    void PlaneScene::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
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
        m_theme->stop();
        m_soundPlay.stop();
        delete m_theme;
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
    
    void PlaneScene::PlaySound()
    {
          int point = rand()%4;
          
          switch(point)
          {
              case 0:
                  m_bufferSound.loadFromFile(DEPLOY_1);
              break;
              
              case 1:
                  m_bufferSound.loadFromFile(DEPLOY_2);
              break;
              
              case 2:
                  m_bufferSound.loadFromFile(DEPLOY_3);
              break;
              
              case 3:
                  m_bufferSound.loadFromFile(DEPLOY_4);
              break;
                  
          }
          m_soundPlay.setBuffer(m_bufferSound);
          m_soundPlay.play();
          
          std::cout<<"le di al play"<<std::endl;
    }
}