#pragma once
#include "State.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <SFML/Audio.hpp>
namespace Zenon
{
    class GameOverState: public State
    {
        public:
            GameOverState(GameDataRef l_data, int l_punctuation);
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void SendDataToWebsite();
            ssize_t Process_http(int sockfd, char *host, char *page, const char *poststr);
        private:
            sf::Sprite m_getBackButton;
            sf::Sprite m_sendDataToServerButton;
            sf::Sprite m_bg;
            std::string m_playerInput;
            sf::Text m_playerText;
            sf::Text m_yourPoints;
            sf::Text m_yourNameInput;
            GameDataRef m_data;
            int m_punctuation;
            bool isSent = false;
            
            sf::Music m_theme;
    };
}
