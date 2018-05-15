#include <sstream>
#include "FaseSeleccionState.hpp"
#include "FichaTrampa.hpp"
#include "DEFINITIONS.hpp"
#include "SaveData.hpp"
#include "PlaneScene.hpp"
#include <iostream>

namespace Zenon {

    FaseSeleccionState::FaseSeleccionState(GameDataRef data) : m_data(data) 
    {
    }

    void FaseSeleccionState::Init() {
        
        m_theme = new sf::Music();
        m_theme->openFromFile(LOADOUT_THEME);
        m_theme->setLoop(true);
        m_theme->setVolume(50);
        m_theme->play();
        
        m_background.setTexture(m_data->assets.GetTexture("SelectBG"));
        
        m_boton.setTexture(m_data->assets.GetTexture("Next"));
        m_boton.setOrigin(m_boton.getGlobalBounds().width / 2, m_boton.getGlobalBounds().height / 2);
        m_boton.setPosition(1600, 70);
        m_boton.scale(0.7, 0.7);

        FichaTrampa * metralleta = new FichaTrampa(m_data, m_data->assets.GetTexture("Metralleta"), m_data->assets.GetTexture("GUI_METRALLETA"), m_data->assets.GetTexture("GUI_METRALLETA_SEL"), m_data->assets.GetTexture("GUI_METRALLETA_BLOCK"), 1, sf::Vector2f(150, 250), PRECIO_TORRETA, PORCENTAJE_TORRETA, CADENCIA_TORRETA, RANGO_TORRETA, REFRESCO_TORRETA, POTENCIA_TORRETA, ATRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_TURRET"));
        FichaTrampa * ametralladora = new FichaTrampa(m_data, m_data->assets.GetTexture("ametralladora"), m_data->assets.GetTexture("GUI_AMETRALLADORA"), m_data->assets.GetTexture("GUI_AMETRALLADORA_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 1, sf::Vector2f(550, 250), PRECIO_AMETRALLADORA, PORCENTAJE_AMETRALLADORA, CADENCIA_AMETRALLADORA, RANGO_AMETRALLADORA, REFRESCO_AMETRALLADORA, POTENCIA_AMETRALLADORA, ATRAP_MACHINEGUN_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_AMETRALLADORA"));
        FichaTrampa * lanzallamas=new FichaTrampa(m_data, m_data->assets.GetTexture("lanzallamas"),m_data->assets.GetTexture("GUI_LANZALLAMAS"),m_data->assets.GetTexture("GUI_LANZALLAMAS_SEL"), m_data->assets.GetTexture("GUI_LANZALLAMAS_BLOCK"),3,sf::Vector2f(750, 250), PRECIO_LANZALLAMAS,PORCENTAJE_LANZALLAMAS,CADENCIA_LANZALLAMAS,RANGO_LANZALLAMAS,REFRESCO_LANZALLAMAS,POTENCIA_LANZALLAMAS,ATRAP_MACHINEGUN_APPEARING_TIME,m_data->assets.GetTexture("DESCRIPTIVE_LANZALLAMAS"));
        FichaTrampa * sanacion=new FichaTrampa(m_data, m_data->assets.GetTexture("sanacion"),m_data->assets.GetTexture("GUI_SANACION"),m_data->assets.GetTexture("GUI_SANACION_SEL"), m_data->assets.GetTexture("GUI_SANACION_BLOCK"),4,sf::Vector2f(350, 250), PRECIO_SANACION,PORCENTAJE_SANACION,CADENCIA_SANACION,RANGO_SANACION,REFRESCO_SANACION,POTENCIA_SANACION, DTRAP_APPEARING_TIME,m_data->assets.GetTexture("DESCRIPTIVE_SANACION"));
        FichaTrampa * adrenalina=new FichaTrampa(m_data, m_data->assets.GetTexture("Adrenalina"),m_data->assets.GetTexture("GUI_ADRENALINA"),m_data->assets.GetTexture("GUI_ADRENALINA_SEL"), m_data->assets.GetTexture("GUI_ADRENALINA_BLOCK"),5,sf::Vector2f(150, 500), PRECIO_ADRENALINA,PORCENTAJE_ADRENALINA,CADENCIA_ADRENALINA,RANGO_ADRENALINA,REFRESCO_ADRENALINA,POTENCIA_ADRENALINA, DTRAP_APPEARING_TIME,m_data->assets.GetTexture("DESCRIPTIVE_ADRENALINA"));


        m_trampasdisp.push_back(metralleta);
        m_trampasdisp.push_back(ametralladora);
        m_trampasdisp.push_back(lanzallamas);
        m_trampasdisp.push_back(sanacion);
        m_trampasdisp.push_back(adrenalina);
      //  m_random=rand()%101;
        m_random = 26;

        if(m_random<25){
            FichaTrampa * hielo = new FichaTrampa(m_data, m_data->assets.GetTexture("Hielo"), m_data->assets.GetTexture("GUI_HIELO"), m_data->assets.GetTexture("GUI_HIELO_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 6, sf::Vector2f(550, 400), PRECIO_TORRE_HIELO, PORCENTAJE_TORRE_HIELO, CADENCIA_TORRE_HIELO, RANGO_TORRE_HIELO, REFRESCO_TORRE_HIELO, POTENCIA_TORRE_HIELO, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_HIELO"));
            m_trampasdisp.push_back(hielo);
        //    std::cout<<"Hola soy el 1"<<std::endl;
        }
        
        if(m_random >=25 && m_random<50){
            FichaTrampa * nuke = new FichaTrampa(m_data, m_data->assets.GetTexture("Hielo"), m_data->assets.GetTexture("GUI_NUKE"), m_data->assets.GetTexture("GUI_NUKE_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 7, sf::Vector2f(550, 400), PRECIO_TORRE_HIELO, PORCENTAJE_TORRE_HIELO, CADENCIA_TORRE_HIELO, RANGO_NUKE, REFRESCO_TORRE_HIELO, POTENCIA_TORRE_HIELO, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_HIELO"));
            m_trampasdisp.push_back(nuke);
        //    std::cout<<"Hola soy el 2"<<std::endl;
        }

        if(m_random >=50 && m_random<75){
            FichaTrampa * hielo = new FichaTrampa(m_data, m_data->assets.GetTexture("Hielo"), m_data->assets.GetTexture("GUI_HIELO"), m_data->assets.GetTexture("GUI_HIELO_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 6, sf::Vector2f(550, 400), PRECIO_TORRE_HIELO, PORCENTAJE_TORRE_HIELO, CADENCIA_TORRE_HIELO, RANGO_TORRE_HIELO, REFRESCO_TORRE_HIELO, POTENCIA_TORRE_HIELO, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_HIELO"));
            m_trampasdisp.push_back(hielo);
        //    std::cout<<"Hola soy el 3"<<std::endl;
            
        }
        
        if(m_random >=75 && m_random<100){
            FichaTrampa * nuke = new FichaTrampa(m_data, m_data->assets.GetTexture("Hielo"), m_data->assets.GetTexture("GUI_NUKE"), m_data->assets.GetTexture("GUI_NUKE_SEL"), m_data->assets.GetTexture("GUI_AMETRALLADORA_BLOCK"), 7, sf::Vector2f(550, 400), PRECIO_TORRE_HIELO, PORCENTAJE_TORRE_HIELO, CADENCIA_TORRE_HIELO, RANGO_NUKE, REFRESCO_TORRE_HIELO, POTENCIA_TORRE_HIELO, DTRAP_APPEARING_TIME, m_data->assets.GetTexture("DESCRIPTIVE_HIELO"));
            m_trampasdisp.push_back(nuke);
         //   std::cout<<"Hola soy el 4"<<std::endl;
        }        

    
        for(int i=0; i<m_trampasdisp.size(); i++)
        {
            m_trampasdisp[i]->SetLocked(m_data->data.IsTrapUnlocked(i));
        }

        this->InitOptions();

    }
    
    
    void FaseSeleccionState::InitOptions()
    {
        m_emptyMap.setTexture(m_data->assets.GetTexture("Empty_Map"));
        m_emptyMap.setScale(0.45,0.45);
        m_emptyMap.setPosition(op1,op2);
        
        //Opciones que se añaden en el mapa
        sf::Sprite m_option1, m_option2, m_option3, m_bottom1, m_bottom2, m_bottom3, m_bottom1off, m_bottom2off, m_bottom3off;
        m_option1.setTexture(m_data->assets.GetTexture("Option1"));
        m_option1.setScale(0.45,0.45);
        m_option1.setPosition(op1,op2);
        
        m_option2.setTexture(m_data->assets.GetTexture("Option2"));
        m_option2.setScale(0.45,0.45);
        m_option2.setPosition(op1,op2);
        
        m_option3.setTexture(m_data->assets.GetTexture("Option3"));
        m_option3.setScale(0.45,0.45);
        m_option3.setPosition(op1,op2);
          
        m_mapOptions.push_back(m_option1);
        m_mapOptions.push_back(m_option2);
        m_mapOptions.push_back(m_option3);
        
        //Botones para seleccionar (ON)
        m_bottom1.setTexture(m_data->assets.GetTexture("Bottom1"));
        m_bottom1.setScale(0.8,0.8);
        m_bottom1.setPosition(bottX, bottY);
        
        m_bottom2.setTexture(m_data->assets.GetTexture("Bottom2"));
        m_bottom2.setScale(0.8,0.8);
        m_bottom2.setPosition(bottX + 400, bottY);
        
        m_bottom3.setTexture(m_data->assets.GetTexture("Bottom3"));
        m_bottom3.setScale(0.8,0.8);
        m_bottom3.setPosition(bottX + 800, bottY);
          
        m_onBottom.push_back(m_bottom1);
        m_onBottom.push_back(m_bottom2);
        m_onBottom.push_back(m_bottom3);
        
        //Botones para seleccionar (OFF)
        m_bottom1off.setTexture(m_data->assets.GetTexture("Bottom1OFF"));
        m_bottom1off.setScale(0.8,0.8);
        m_bottom1off.setPosition(bottX ,bottY);
        
        m_bottom2off.setTexture(m_data->assets.GetTexture("Bottom2OFF"));
        m_bottom2off.setScale(0.8,0.8);
        m_bottom2off.setPosition(bottX + 400, bottY);
        
        m_bottom3off.setTexture(m_data->assets.GetTexture("Bottom3OFF"));
        m_bottom3off.setScale(0.8,0.8);
        m_bottom3off.setPosition(bottX + 800, bottY);
          
        m_offBottom.push_back(m_bottom1off);
        m_offBottom.push_back(m_bottom2off);
        m_offBottom.push_back(m_bottom3off);
        
        //Vector de boleanos
        for(int i = 0; i<m_numBool; i++)
        {
            m_boolVector.push_back(false);
        }
        
        //Save data para el dinero
        m_dineroJugador=m_data->data.GetMoney();
        
        //Letras del dinero
        m_moneyText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_moneyText.setString(std::to_string(m_dineroJugador));
        m_moneyText.setCharacterSize(40);
        m_moneyText.setOrigin(m_moneyText.getGlobalBounds().width / 2, m_moneyText.getGlobalBounds().height / 2);
        m_moneyText.setPosition(1150, 50);
        
        m_bgMoney.setTexture(this->m_data->assets.GetTexture("MoneyButton"));
        m_bgMoney.setOrigin(m_bgMoney.getGlobalBounds().width/2,m_bgMoney.getGlobalBounds().height/2);
        m_bgMoney.scale(0.7,0.7);
        m_bgMoney.setPosition(m_moneyText.getPosition().x-7, m_moneyText.getPosition().y + 10);
        m_boton.setPosition(m_bgMoney.getPosition().x + 400, m_bgMoney.getPosition().y);
        
        m_introText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_introText.setString("SELECCIONA TUS ARMAS");
        m_introText.setCharacterSize(72);
        m_introText.setPosition(m_boton.getPosition().x - 1470, m_boton.getPosition().y- 50);
        
        m_advertiseText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_advertiseText.setString("Elige alguna ayuda (Cuidado, puedes quedarte sin recursos)");
        m_advertiseText.setCharacterSize(40);
        m_advertiseText.setPosition(600, 720);
    }

    void FaseSeleccionState::HandleInput() {
        sf::Event event;

        while (this->m_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                this->m_data->window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (int i = 0; i < m_trampasdisp.size(); i++) {
                    if (m_trampasdisp.at(i)->IsClicked()) {
                        m_trampasdisp.at(i)->GestionSeleccion();
                    }
                }

            }

            if (this->m_data->input.IsSpriteClicked(this->m_boton, sf::Mouse::Left, m_data->window)) {
                this->ChangeState();
            }
            
                        //Compra 
            for(int i = 0; i<m_onBottom.size();i++)
            {
                if(this->m_data->input.IsSpriteClicked(this->m_onBottom[i], sf::Mouse::Left, m_data->window) && m_boolVector[i] == false)
                {
                    m_boolVector[i] = true;  
                    m_Sum = i;
                    m_downMoney = true;
                }
            }  
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
            {
             this->m_data->window.close();   
             m_data->window.create(sf::VideoMode(1920, 1088), "We Will Not Fall" , sf::Style::Fullscreen);
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                this->m_data->window.close();  
                m_data->window.create(sf::VideoMode(1920, 1088), "We Will Not Fall" , sf::Style::Titlebar | sf::Style::Close);
            }
        }
    }

    void FaseSeleccionState::Update(float dt) {
        if(m_downMoney == true)
        {
            if(m_downMoney == true)
            {
                switch (m_Sum)
                {
                    case 0:
                        m_whSum = 150;
                    break;

                    case 1:
                        m_whSum = 150;
                    break;

                    case 2:
                        m_whSum = 500;
                    break;
                }
                m_dineroJugador -= m_whSum;
                m_moneyText.setString(std::to_string(m_dineroJugador));
                m_downMoney = false;  
            }
        }

    }

    void FaseSeleccionState::Draw(float dt) {
        this->m_data->window.clear(sf::Color::Black);

        this->m_data->window.draw(m_background);
        
        for (int i = 0; i < m_trampasdisp.size()-1; i++) {
            m_trampasdisp.at(i)->Draw();
        }

        this->m_data->window.draw(m_boton);
        
        this->m_data->window.draw(m_emptyMap); 
        for ( int i = 0; i < m_numBool; i++)
        {
            if(m_boolVector[i]==false)
            {
                this->m_data->window.draw(m_onBottom[i]);
            }
            else
            {
                this->m_data->window.draw(m_offBottom[i]);
                this->m_data->window.draw(m_mapOptions[i]);
            }
        }
        
        this->m_data->window.draw(m_bgMoney);
        
        this->m_data->window.draw(m_introText);
        
        this->m_data->window.draw(m_moneyText);
        
        this->m_data->window.draw(m_advertiseText);
        
        this->m_data->window.display();
    }

    void FaseSeleccionState::ChangeState() {
        for (int i = 0; i < m_trampasdisp.size(); i++) 
        {
            if (m_trampasdisp.at(i)->IsSelected())
                m_trampasSel.push_back(m_trampasdisp.at(i));
        }
        
        m_data->data.SetMoney(m_dineroJugador);
        std::cout<<"Cuando salgo del FaseSeleccion, hay: "<<m_trampasSel.size()<<std::endl;

        if (m_trampasSel.size() > 0) {
            m_trampasSel.push_back(m_trampasdisp.at(m_trampasdisp.size()-1));
            m_data->machine.AddState(StateRef(new PlaneScene(this->m_data, m_trampasSel, m_theme)));
        }
    }
}