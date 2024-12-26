#pragma once

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

namespace Core {
    class InputManager
    {
    public:
        static void Initialize();
        static void Update();
        static bool KeyPressed(int key);
        static bool MouseButtonPressed(int button);
        static double GetMouseX();
        static double GetMouseY();

    private:
        static double _mouseX, _mouseY;
    };
}

#endif //INPUTMANAGER_HPP
