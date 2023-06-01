#pragma once

#include "SDL.h"  // Include the SDL library
#include <vector>  // Include the vector library for vector container

class GameObject;  // Forward declaration of the GameObject class

class State // This is the abstract base class for all states
{
public:
    State() = default;
    virtual ~State() = default;  // Modern alternative to {}

    // Pure virtual functions that must be defined in subclasses
    virtual void Enter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

    // Virtual function that can be overridden in subclasses (optional)
    virtual void Resume() { };
};

class TitleState : public State
{
    float timer = 0.0f;  // Timer for state transition
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};

class MenuState : public State
{
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};

class CreditState : public State
{
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};

class GameState : public State
{
    static const int kPlayerSpeed = 400;  // Speed of the player object
    std::vector<GameObject*> m_gameObjects;  // Vector of GameObject pointers
    GameObject* m_pPlayer;  // Pointer to the player object
    float timer = 0.0f;  // Timer for state transition
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
    virtual void Resume() override;
};

class PauseState : public State
{
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};

class WinState : public State
{
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};

class LoseState : public State
{
public:
    virtual void Enter() override;
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void Exit() override;
};
