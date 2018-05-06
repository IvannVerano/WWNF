#include "PlaneReturnScene.hpp"
#include "SplashState.hpp"
#include "LevelSelectorState.hpp"

namespace Zenon
{
    PlaneReturnScene::PlaneReturnScene(GameDataRef l_data, bool success): m_data(l_data)
    {
        m_destinyPoint = sf::Vector2f(100, 800);
        isSuccess = success;
    }
    
    void PlaneReturnScene::Init()
    {
        
        m_textSuccess.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_textSuccess.setCharacterSize(15);
        
        if(isSuccess)
        {
            m_textSuccess.setString("MISION CUMPLIDA");
            m_textSuccess.setColor(sf::Color::Green);
        }
        else
        {
            m_textSuccess.setString("MISION FRACASADA");
            m_textSuccess.setColor(sf::Color::Red);
        }
        
        m_textSuccess.setOrigin(m_textSuccess.getGlobalBounds().width/2, m_textSuccess.getGlobalBounds().height/2);
        
        m_plane.setTexture(m_data->assets.GetTexture("Plane"));
        m_plane.setOrigin(m_plane.getGlobalBounds().width/2, m_plane.getGlobalBounds().height/2);
        m_destiny.setTexture(m_data->assets.GetTexture("MapMarker"));
        m_destiny.setOrigin(m_destiny.getGlobalBounds().width/2, m_destiny.getGlobalBounds().height/2);
        m_background.setTexture(m_data->assets.GetTexture("CleanMap"));
        m_nextButton.setTexture(m_data->assets.GetTexture("Desplegar"));
        m_nextButton.setOrigin(m_nextButton.getGlobalBounds().width/2, m_nextButton.getGlobalBounds().height/2);
        
        
        m_destiny.setPosition(m_destinyPoint);
        m_nextButton.setPosition(m_destinyPoint.x + 100, m_destinyPoint.y + 50);
       
        m_plane.setPosition(m_data->reward.GetLevelLocation());
        m_textSuccess.setPosition(m_plane.getPosition().x - 100, m_plane.getPosition().y - 100);
        
        if(isSuccess)
        {
            m_civilians.setString("Civiles rescatados: " + std::to_string(m_data->reward.GetCiviliansRescued()));
            m_civilians.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_civilians.setCharacterSize(10);
            m_civilians.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 30);
            m_confidenceReward.setString("Confianza recuperada: " + std::to_string(m_data->reward.GetConfidenceRestablish()));
            m_confidenceReward.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_confidenceReward.setCharacterSize(10);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_money.setString("Ingresos por exito: " + std::to_string(m_data->reward.GetMoney()));
            m_money.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_money.setCharacterSize(10);
            m_money.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            
            switch(m_data->reward.GetIdTrapRewarded())
            {
                case 3:
                    m_trapUnlocked.setString("Trampa desbloqueada:\nCristal de sanacion");
                break;
                case 4:
                    m_trapUnlocked.setString("Trampa desbloqueada:\nLanzallamas");
                break;
                case 5:
                    m_trapUnlocked.setString("Trampa desbloqueada:\nAdrenalina en gas");
                break;
                case -1:
                    m_trapUnlocked.setString("No desbloqueas trampas");
                break;
            }
            m_trapUnlocked.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_trapUnlocked.setCharacterSize(10);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            
        }
        else
        {
            m_civilians.setString("Todos los civiles han muerto");
            m_civilians.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_civilians.setCharacterSize(10);
            m_civilians.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 30);
            m_confidenceReward.setString("Confianza perdida: " + std::to_string(3));
            m_confidenceReward.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_confidenceReward.setCharacterSize(10);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_money.setString("Te crees que vas a cobrar?");
            m_money.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_money.setCharacterSize(10);
            m_money.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 55);
            m_trapUnlocked.setString("No desbloqueas trampas");
            m_trapUnlocked.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_trapUnlocked.setCharacterSize(10);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
        }
        
        m_nextButton.scale(0.3,0.3);
        m_destiny.scale(0.8,0.8);
        m_plane.scale(0.2,0.2); 
        
        m_trajectory = m_destinyPoint - m_plane.getPosition();
        
        m_camera.setCenter(m_plane.getPosition());
        m_camera.setSize(1920, 1080);
        m_camera.zoom(0.2f);
        
        float module = Module(m_trajectory);
        m_normalized = Normalize(m_trajectory, module);
        
        this->SetPlaneRotation();
        
        m_infobox.setTexture(m_data->assets.GetTexture("Infobox"));
        m_infobox.setOrigin(m_infobox.getGlobalBounds().width/2, m_infobox.getGlobalBounds().height/2);
        m_infobox.setPosition(m_plane.getPosition().x -130, m_plane.getPosition().y -50 );
        m_infobox.scale(0.3,0.3);
        
        
    }
    
    void PlaneReturnScene::HandleInput()
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
    
    void PlaneReturnScene::Update(float dt)
    {
        m_destiny.rotate(20*dt);
        if(!hasArrived)
        {
            m_plane.move(m_normalized.x*dt*PLANE_SPEED, m_normalized.y*dt*PLANE_SPEED);
            m_camera.setCenter(m_plane.getPosition());
            m_textSuccess.setPosition(m_plane.getPosition().x - 130, m_plane.getPosition().y - 100);
            m_infobox.setPosition(m_plane.getPosition().x -130, m_plane.getPosition().y -50 );
            m_civilians.setPosition(m_textSuccess.getPosition().x -50, m_textSuccess.getPosition().y + 25);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 50, m_textSuccess.getPosition().y + 35);
            m_money.setPosition(m_textSuccess.getPosition().x - 50, m_textSuccess.getPosition().y + 45);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 50, m_textSuccess.getPosition().y + 55);
        }
        if (m_plane.getGlobalBounds().intersects(m_destiny.getGlobalBounds()))
        {
            hasArrived = true;
        }
    }
    
    void PlaneReturnScene::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.setView(m_camera);
        this->m_data->window.draw(m_background);
        this->m_data->window.draw(m_infobox);
        this->m_data->window.draw(m_textSuccess);
        
        if(m_clockApparition.getElapsedTime().asSeconds() > 0.5f)
            this->m_data->window.draw(m_civilians);
        if(m_clockApparition.getElapsedTime().asSeconds() > 1.0f)
            this->m_data->window.draw(m_confidenceReward);
        if(m_clockApparition.getElapsedTime().asSeconds() > 1.5f)
            this->m_data->window.draw(m_money);
        if(m_clockApparition.getElapsedTime().asSeconds() > 2.0f)
            this->m_data->window.draw(m_trapUnlocked);
        
        
        this->m_data->window.draw(m_destiny);
        this->m_data->window.draw(m_plane);
        if(hasArrived)
        {
            this->m_data->window.draw(m_nextButton);
        }
        this->m_data->window.display();
    }
    
    void PlaneReturnScene::StartGame()
    {
        this->m_data->machine.AddState(StateRef(new LevelSelectorState(m_data, isSuccess)));
    }
    
    void PlaneReturnScene::SetPlaneRotation()
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