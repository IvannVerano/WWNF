#include "PlaneReturnScene.hpp"
#include "SplashState.hpp"
#include "LevelSelectorState.hpp"
#include "GameOverState.hpp"

namespace Zenon
{
    PlaneReturnScene::PlaneReturnScene(GameDataRef l_data, bool success): m_data(l_data)
    {
        m_destinyPoint = sf::Vector2f(100, 3000);
        isSuccess = success;
        
        m_theme = new sf::Music();
        if(isSuccess)
        {
            m_theme->openFromFile(VICTORY_THEME);
        }
        else
        {
            m_theme->openFromFile(FAILURE_THEME);
            m_data->data.SetConfidenceLevel(-3);
            std::cout<<"Nivel de confianza: "<<m_data->data.GetConfidenceLevel()<<std::endl;
        }
        
        m_theme->setVolume(50);
        m_theme->play();
    }
    
    void PlaneReturnScene::Init()
    {
        
        m_textSuccess.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_textSuccess.setCharacterSize(40);
        
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
        m_nextButton.setPosition(m_plane.getPosition().x - 100, m_plane.getPosition().y);
       
        m_plane.setPosition(960, 540);
        m_textSuccess.setPosition(m_plane.getPosition().x - 100, m_plane.getPosition().y - 100);
        
        
        m_background.setOrigin(m_data->reward.GetReturnLocation());
        m_background.setPosition(m_plane.getPosition());
        m_background.scale(5.0,5.0);
        
        if(isSuccess)
        {
            m_civilians.setString("Civiles rescatados: " + std::to_string(m_data->reward.GetCiviliansRescued()));
            m_civilians.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_civilians.setCharacterSize(40);
            m_civilians.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 30);
            m_confidenceReward.setString("Confianza recuperada: " + std::to_string(m_data->reward.GetConfidenceRestablish()));
            m_confidenceReward.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_confidenceReward.setCharacterSize(40);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_money.setString("Ingresos por exito: " + std::to_string(m_data->reward.GetMoney()));
            m_money.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_money.setCharacterSize(40);
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
            m_trapUnlocked.setCharacterSize(40);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            
        }
        else
        {
            m_civilians.setString("Todos los civiles han muerto");
            m_civilians.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_civilians.setCharacterSize(30);
            m_civilians.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 30);
            m_confidenceReward.setString("Confianza perdida: " + std::to_string(3));
            m_confidenceReward.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_confidenceReward.setCharacterSize(30);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_money.setString("Te crees que vas a cobrar?");
            m_money.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_money.setCharacterSize(30);
            m_money.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 55);
            m_trapUnlocked.setString("No desbloqueas trampas");
            m_trapUnlocked.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
            m_trapUnlocked.setCharacterSize(30);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 20, m_textSuccess.getPosition().y + 50);
        }
        
        m_trajectory = m_destinyPoint - m_plane.getPosition();
        
        float module = Module(m_trajectory);
        m_normalized = Normalize(m_trajectory, module);
        
        this->SetPlaneRotation();
        
        m_infobox.setTexture(m_data->assets.GetTexture("Infobox"));
        m_infobox.setOrigin(m_infobox.getGlobalBounds().width/2, m_infobox.getGlobalBounds().height/2);
        m_infobox.setPosition(m_plane.getPosition().x -400, m_plane.getPosition().y -350 );
        
        
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
            m_background.move(m_normalized.x*dt*PLANE_SPEED_RETURN * -1, m_normalized.y*dt*PLANE_SPEED_RETURN *-1);
            m_destiny.move(m_normalized.x*dt*PLANE_SPEED_RETURN * -1, m_normalized.y*dt*PLANE_SPEED_RETURN *-1);
            m_textSuccess.setPosition(m_plane.getPosition().x - 350, m_plane.getPosition().y - 410);
            m_infobox.setPosition(m_plane.getPosition().x -300, m_plane.getPosition().y -250 );
            m_nextButton.setPosition(m_plane.getPosition().x - 300, m_plane.getPosition().y +10);
            m_civilians.setPosition(m_textSuccess.getPosition().x - 130, m_textSuccess.getPosition().y + 65);
            m_confidenceReward.setPosition(m_textSuccess.getPosition().x - 130, m_textSuccess.getPosition().y + 115);
            m_money.setPosition(m_textSuccess.getPosition().x - 130, m_textSuccess.getPosition().y + 165);
            m_trapUnlocked.setPosition(m_textSuccess.getPosition().x - 130, m_textSuccess.getPosition().y + 235);
        }
        if (m_plane.getGlobalBounds().intersects(m_destiny.getGlobalBounds()))
        {
            hasArrived = true;
        }
    }
    
    void PlaneReturnScene::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.draw(m_background);
        this->m_data->window.draw(m_infobox);
        this->m_data->window.draw(m_textSuccess);
        
        if(m_clockApparition.getElapsedTime().asSeconds() > 1.0f)
            this->m_data->window.draw(m_civilians);
        if(m_clockApparition.getElapsedTime().asSeconds() > 2.0f)
        {
            this->m_data->window.draw(m_confidenceReward);
            if(!isSounded)
            {
                this->PlaySound();
                isSounded = true;
            }
        }
        if(m_clockApparition.getElapsedTime().asSeconds() > 3.0f)
            this->m_data->window.draw(m_money);
        if(m_clockApparition.getElapsedTime().asSeconds() > 4.0f)
            this->m_data->window.draw(m_trapUnlocked);
        if(m_clockApparition.getElapsedTime().asSeconds()> 5.0f)
            this->m_data->window.draw(m_nextButton);
        
        
        this->m_data->window.draw(m_destiny);
        this->m_data->window.draw(m_plane);
        this->m_data->window.display();
    }
    
    void PlaneReturnScene::StartGame()
    {
        m_theme->stop();
        delete m_theme;
        if(m_data->data.GetConfidenceLevel() > 0)
        {
            m_data->data.SaveChanges();
            this->m_data->machine.AddState(StateRef(new LevelSelectorState(m_data, isSuccess, true, false)));
        }
        else
        {
            this->m_data->machine.AddState(StateRef(new GameOverState(this->m_data, m_data->data.GetMoney())));
        }
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
    
    void PlaneReturnScene::PlaySound()
    {
        int pointer = rand()%3;
        
        switch(pointer)
        {
            case 0:
                if(isSuccess)
                    m_bufferSound.loadFromFile(VICTORY_1);
                else
                    m_bufferSound.loadFromFile(DEFEAT_1);
            break;
            
            case 1:
                if(isSuccess)
                    m_bufferSound.loadFromFile(VICTORY_2);
                else
                    m_bufferSound.loadFromFile(DEFEAT_2);
            break;
            
            case 2:
                if(isSuccess)
                    m_bufferSound.loadFromFile(VICTORY_3);
                else
                    m_bufferSound.loadFromFile(DEFEAT_3);
            break;
        }
        
        m_soundPlay.setBuffer(m_bufferSound);
        m_soundPlay.play();
    }
}