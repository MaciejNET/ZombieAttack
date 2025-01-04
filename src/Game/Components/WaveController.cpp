#include "WaveController.hpp"

#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <random>

#include "Game/GameObjects/EntityFactory.hpp"

void WaveController::OnCreate()
{
}

void WaveController::OnUpdate(float deltaTime)
{
    auto& waveComponent = _entity.GetComponent<Scene::WaveComponent>();
    DrawWaveInfo(waveComponent);
    if (waveComponent.ZombiesLeft == 0)
    {
        if (_coolDown <= 0.0f)
        {
            waveComponent.WaveNumber++;
            GenerateWave(waveComponent);
            _coolDown = _coolDownTime;
        }
        else
        {
            _coolDown -= deltaTime;
        }
    }
}

void WaveController::GenerateWave(Scene::WaveComponent& waveComponent) const
{
    switch (waveComponent.WaveNumber)
    {
        case 1:
            waveComponent.ZombiesLeft = 3;
            SpawnZombie(3);
            break;
        case 2:
            waveComponent.ZombiesLeft = 5;
            SpawnZombie(5);
            break;
        case 3:
            waveComponent.ZombiesLeft = 8;
            SpawnZombie(8);
            break;
        case 4:
            waveComponent.ZombiesLeft = 11;
            SpawnZombie(11);
            break;
        case 5:
            waveComponent.ZombiesLeft = 14;
            SpawnZombie(14);
            break;
        case 6:
            waveComponent.ZombiesLeft = 17;
            SpawnZombie(17);
            break;
        case 7:
            waveComponent.ZombiesLeft = 20;
            SpawnZombie(20);
            break;
        case 8:
            waveComponent.ZombiesLeft = 23;
            SpawnZombie(23);
            break;
        case 9:
            waveComponent.ZombiesLeft = 26;
            SpawnZombie(26);
            break;
        case 10:
            waveComponent.ZombiesLeft = 50;
            SpawnZombie(50);
            break;
        default: break;
    }
}

void WaveController::SpawnZombie(const int count) const
{
    const auto scene = _entity.GetScene();
    const float distribution = 25.0f + static_cast<float>(count) / 10.0f;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dis(-distribution, distribution);

    for (int i = 0; i < count; i++)
    {
        const float x = dis(gen);
        constexpr float y = 0.0f;
        const float z = dis(gen);

        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

        EntityFactory::CreateZombie(*scene, transform);
    }
}

void WaveController::DrawWaveInfo(const Scene::WaveComponent &waveComponent) const
{
    ImGuiIO& io = ImGui::GetIO();
    float padding = 10.0f;
    ImVec2 windowSize = ImVec2(200.0f, 100.0f);
    ImVec2 windowPos = ImVec2(io.DisplaySize.x - windowSize.x - padding, padding);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

    int minutes = static_cast<int>(_coolDown) / 60;
    int seconds = (static_cast<int>(_coolDown) % 60)+1;

    if (waveComponent.ZombiesLeft > 0)
    {
        minutes = 0;
        seconds = 0;
    }

    ImGui::Begin("Wave Info");
    ImGui::Text("Wave: %d", waveComponent.WaveNumber);
    ImGui::Text("Zombies Left: %d", waveComponent.ZombiesLeft);
    ImGui::Text("Next Wave in: %02d:%02d", minutes, seconds);
    ImGui::End();
}

