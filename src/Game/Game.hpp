#ifndef GAME_HPP
#define GAME_HPP
#include "Scene/Scene.hpp"

class Game
{
public:
    Game();
    void Init();
    void Update(float deltaTime);
    void Stop() { _isStopped = true; }
    void Start() { _isStopped = false; }
    void DrawMenu();
private:
    Scene::Scene _scene;
    bool _isStopped{true};
};



#endif //GAME_HPP
