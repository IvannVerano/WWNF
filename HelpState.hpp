#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"


namespace Zenon{
    class HelpState:public State {
    public:
        HelpState(GameDataRef l_data);
        ~HelpState();
        void Init();
        void HandleInput();
        void NewGame();
        void Update(float dt);
        void Draw(float dt);
    private:
        GameDataRef m_data;
    };
}



