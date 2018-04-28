/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameOverState.cpp
 * Author: user
 * 
 * Created on 24 de abril de 2018, 18:24
 */

#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"


namespace Zenon
{
    GameOverState::GameOverState(GameDataRef l_data, int l_punctuation): m_data(l_data)
    {
        m_punctuation = l_punctuation;
    }
    
    void GameOverState::Init()
    {
        m_punctuation += m_data->data.GetGeneralPunctuation();
        
        m_failText.setString("GAME OVER NEGGU");
        m_failText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_failText.setPosition(100,100);
        
        m_yourPoints.setString("Civiles rescatados: "+std::to_string(m_data->data.GetGeneralPunctuation())+"\n\nDinero acumulado: "+std::to_string(m_punctuation - m_data->data.GetGeneralPunctuation())+"\n\nPUNTUACION FINAL: " + std::to_string(m_punctuation));
        m_yourPoints.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_yourPoints.setPosition(100,200);
        
        m_yourNameInput.setString("Tu nombre: ");
        m_yourNameInput.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_yourNameInput.setPosition(100,400);
        
        m_playerText.setFont(m_data->assets.GetFont("FUENTE_DINERO"));
        m_playerText.setPosition(220,400);
        
        
        //Botones para terminar el juego
        m_getBackButton.setTexture(m_data->assets.GetTexture("Metralleta"));
        m_sendDataToServerButton.setTexture(m_data->assets.GetTexture("Defensa"));
        m_getBackButton.setOrigin(m_getBackButton.getGlobalBounds().width/2, m_getBackButton.getGlobalBounds().height/2);
        m_getBackButton.setPosition(200,600);
        m_sendDataToServerButton.setOrigin(m_sendDataToServerButton.getGlobalBounds().width/2, m_sendDataToServerButton.getGlobalBounds().height/2);
        m_sendDataToServerButton.setPosition(400,600);
    }
    
    void GameOverState::HandleInput()
    {
        sf::Event event;
        while (this->m_data->window.pollEvent(event)) 
        {
            
            if (event.type == sf::Event::TextEntered)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    if(m_playerInput.size()>0)
                    {
                        m_playerInput.erase(m_playerInput.end()-1);
                        m_playerText.setString(m_playerInput);
                    }
                }
                else if(m_playerInput.size()<MAXIMUM_CHAR)
                {
                    m_playerInput +=event.text.unicode;
                    m_playerText.setString(m_playerInput);
                }
            }   
            if(m_data->input.IsSpriteClicked(m_sendDataToServerButton, sf::Mouse::Left, m_data->window))
            {
                if(!isSent)
                {
                    this->SendDataToWebsite();
                    isSent = true;
                }
            }
        }
    }
    
    void GameOverState::Update(float dt)
    {
    }
    
    void GameOverState::Draw(float dt)
    {
        this->m_data->window.clear(sf::Color::Black);
        this->m_data->window.draw(m_failText);
        this->m_data->window.draw(m_getBackButton);
        this->m_data->window.draw(m_sendDataToServerButton);
        this->m_data->window.draw(m_playerText);
        this->m_data->window.draw(m_yourPoints);
        this->m_data->window.draw(m_yourNameInput);
        this->m_data->window.display();
    }
    
    void GameOverState::SendDataToWebsite()
    {
        int sockfd;
        struct sockaddr_in servaddr;

        char **pptr;
        //********** You can change. Puy any values here *******
        char *hname = "wwnfcompanion.000webhostapp.com";
        char *page = "/inserta_resultados.php";
        std::string result = std::to_string(m_punctuation);
        std::string nombre = "&nombre=";
        std::string init = "resultado=";
        std::string fin = "\n";
        std::string body = init+result+nombre+m_playerInput+fin;
        const char *poststr = body.c_str();
        //*******************************************************

        char str[50];
        struct hostent *hptr;
        if ((hptr = gethostbyname(hname)) == NULL) {
            fprintf(stderr, " Server down error for host: %s: %s",
                    hname, hstrerror(h_errno));
            exit(1);
        }
        printf("hostname: %s \n", hptr->h_name);
        if (hptr->h_addrtype == AF_INET
            && (pptr = hptr->h_addr_list) != NULL) {
            printf("address: %s\n",
                   inet_ntop(hptr->h_addrtype, *pptr, str,
                             sizeof(str)));
        } else {
            fprintf(stderr, "Error call inet_ntop \n");
        }

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(80);
        inet_pton(AF_INET, str, &servaddr.sin_addr);

        connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
        Process_http(sockfd, hname, page, poststr);
        close(sockfd);
        m_data->data.Reset();
        m_data->reward.ResetpanicLevels();
        m_data->machine.AddState(StateRef(new LevelSelectorState(this->m_data, false)));
    }
    
    ssize_t GameOverState::Process_http(int sockfd, char *host, char *page, const char *poststr)
    {
        char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
        ssize_t n;
        snprintf(sendline, MAXSUB,
                 "POST %s HTTP/1.0\r\n"
                 "Host: %s\r\n"
                 "Content-type: application/x-www-form-urlencoded\r\n"
                 "Content-length: %d\r\n\r\n"
                 "%s", page, host, strlen(poststr), poststr);
        write(sockfd, sendline, strlen(sendline));
        std::cout<<sendline<<std::endl;
        while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
            recvline[n] = '\0';
            printf("%s", recvline);  // <-- this
        }
        return n;

    }
}

