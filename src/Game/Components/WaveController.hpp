#ifndef WAVECONTROLLER_HPP
#define WAVECONTROLLER_HPP
#include "ECS/ScriptableEntity.hpp"
#include "Scene/Components.hpp"

class WaveController final : public ECS::ScriptableEntity
{
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;

    void GenerateWave(Scene::WaveComponent& waveComponent) const;
    void SpawnZombie(int count) const;
    void DrawWaveInfo(const Scene::WaveComponent& waveComponent) const;
    float _coolDown = 0.0f;
};

#endif //WAVECONTROLLER_HPP
