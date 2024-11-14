#ifndef APP_HPP
#define APP_HPP
#include "Game/Game.hpp"

class App
{
public:
    App();
    void Run();

private:
    Game _game;
    float _deltaTime{};
};



#endif //APP_HPP
