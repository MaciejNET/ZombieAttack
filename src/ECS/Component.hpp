#pragma once

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace ECS {
    struct Component
    {
        virtual ~Component() = default;
    };
}

#endif //COMPONENT_HPP
