#ifndef ZOMBIEATTACK_IDGENERATOR_H
#define ZOMBIEATTACK_IDGENERATOR_H

#include <atomic>

namespace ECS {
    class IdGenerator
    {
    public:
        static int GetNextId()
        {
            return ++_id;
        }
    private:
        static std::atomic<int> _id;
    };

    std::atomic<int> IdGenerator::_id = 0;
}

#endif //ZOMBIEATTACK_IDGENERATOR_H
