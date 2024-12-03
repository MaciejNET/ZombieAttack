cmake_minimum_required(VERSION 3.29)
project(ZombieAttack)

set(CMAKE_CXX_STANDARD 20)

find_library(GLFW_LIBRARY NAMES glfw3 PATHS "${CMAKE_SOURCE_DIR}/dependencies/lib")
find_library(ASSIMP_LIBRARY NAMES libassimp.5.4.3.dylib PATHS "${CMAKE_SOURCE_DIR}/dependencies/lib")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/include")

if(APPLE)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COCOA_LIBRARY Cocoa)
endif()

include_directories(.)
include_directories(src)

add_executable(ZombieAttack
        src/glad.c
        main.cpp
        src/Core/VAO.cpp
        src/Core/VAO.hpp
        src/Core/VBO.cpp
        src/Core/VBO.hpp
        src/Core/EBO.cpp
        src/Core/EBO.hpp
        src/Core/Mesh.cpp
        src/Core/Mesh.hpp
        src/Core/Shader.cpp
        src/Core/Shader.hpp
        src/Core/Camera.cpp
        src/Core/Camera.hpp
        src/Core/WindowManager.cpp
        src/Core/WindowManager.hpp
        src/Core/InputManager.cpp
        src/Core/InputManager.hpp
        src/Events/Event.hpp
        src/Events/EventBus.hpp
        src/Events/EventBus.cpp
        src/Events/KeyHeldEvent.hpp
        src/Events/KeyPressedEvent.hpp
        src/Events/KeyReleasedEvent.hpp
        src/Events/MouseButtonPressedEvent.hpp
        src/Events/MouseMovedEvent.hpp
        src/App.cpp
        src/App.hpp
        src/ECS/Entity.hpp
        src/ECS/Component.hpp
        src/Scene/Scene.cpp
        src/Scene/Scene.hpp
        src/Scene/Components.hpp
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.hpp
        src/Core/BaseShapes.hpp
        src/Core/Macros.hpp
        src/ECS/ScriptableEntity.hpp
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/Components/PlayerController.cpp
        src/Game/Components/PlayerController.hpp
        src/Game/Components/ZombieController.cpp
        src/Game/Components/ZombieController.hpp
        src/Game/Components/BulletController.cpp
        src/Game/Components/BulletController.hpp
        src/ECS/Entity.cpp
)

if(APPLE)
    target_link_libraries(ZombieAttack ${GLFW_LIBRARY} ${ASSIMP_LIBRARY} ${COREFOUNDATION_LIBRARY} ${COREGRAPHICS_LIBRARY} ${IOKIT_LIBRARY} ${COCOA_LIBRARY})
else()
    target_link_libraries(ZombieAttack ${GLFW_LIBRARY} ${ASSIMP_LIBRARY})
endif()
