#ifndef ZOMBIEATTACK_IDGENERATOR_H
#define ZOMBIEATTACK_IDGENERATOR_H

#include <mutex>

namespace ECS {
    class IdGenerator
    {
    public:
        static int GetNextId()
        {
            std::lock_guard lock(_mutex);
            return ++_id;
        }
    private:
        static int _id;
        static std::mutex _mutex;
    };

    int IdGenerator::_id = 0;
    std::mutex IdGenerator::_mutex;
}

#endif //ZOMBIEATTACK_IDGENERATOR_H
