#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include <iostream>
#include <vector>

#include "GameItems.hpp"

class Inventory
{
public:
    Inventory()
        : _selectedItem(typeid(Pistol))
    {
        AddItem<Pistol>();
        AddItem<BurstRifle>();
        AddItem<Shotgun>();
        AddItem<Rifle>();
        AddItem<MiniGun>();
    }
    ~Inventory() = default;

    template<typename T, typename... Args>
    void AddItem(Args&&... args)
    {
        static_assert(std::is_base_of_v<GameItem, T>, "T must be derived from GameItem");
        _items[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    void UseSelectedItem(const PlayerCoordinates& playerCoordinates, Scene::Scene& scene, const float deltaTime)
    {
        const auto item = _items[_selectedItem];
        item->Use(playerCoordinates, scene, deltaTime);
    }

    void Update(const float deltaTime)
    {
        const auto item = _items[_selectedItem];
        item->Update(deltaTime);
    }

    void SelectNextItem()
    {
        if (_items.empty())
        {
            return;
        }

        static const std::vector<std::type_index> order = {
            typeid(Pistol),
            typeid(BurstRifle),
            typeid(Shotgun),
            typeid(Rifle),
            typeid(MiniGun),
            typeid(Health),
            typeid(Trap)
        };

        auto it = std::ranges::find(order, _selectedItem);
        if (it == order.end())
        {
            return;
        }

        do
        {
            ++it;
            if (it == order.end())
            {
                it = order.begin();
            }
        } while (!_items.contains(*it));

        _selectedItem = *it;
        std::cout << "Selected item: " << _selectedItem.name() << std::endl;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<GameItem>> _items;
    std::type_index _selectedItem;
};

#endif //INVENTORY_HPP
