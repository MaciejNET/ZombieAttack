#ifndef ZOMBIEATTACK_IDGENERATOR_H
#define ZOMBIEATTACK_IDGENERATOR_H

#include <mutex>

namespace ECS {
    class IdGenerator
    {
    private:
        static int _id;
        static std::mutex _mutex;

    public:
        static int GetNextId()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return ++_id;
        }
    };

    int IdGenerator::_id = 0;
    std::mutex IdGenerator::_mutex;
}

#endif //ZOMBIEATTACK_IDGENERATOR_H
