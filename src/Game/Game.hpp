#ifndef GAME_HPP
#define GAME_HPP
#include "Scene/Scene.hpp"

class Game
{
public:
    Game();
    void Init();
    void Update(float deltaTime);
private:
    Scene::Scene _scene;
};



#endif //GAME_HPP
