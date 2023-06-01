#include <iostream>  // Include the iostream library for input/output
#include "Game.h"  // Include the "Game.h" header file
#include "StateManager.h"  // Include the "StateManager.h" header file
#include "States.h"  // Include the "States.h" header file

Game::Game()
    : is_running(false)
    , g_window(nullptr)
    , g_Renderer(nullptr)
    , g_keyState(nullptr)
{

}

Game& Game::GetInstance()
{
    static Game* pInstance = new Game();
    return *pInstance;
}

int Game::Init(const char* title, int xPos, int yPos)
{
    std::cout << "Initializing engine..." << std::endl;
    // Call to SDL_Init(). Initialize SDL and video subsystem
    int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
    if (errorCode == 0)
    {
        std::cout << "SDL_Init() succeeded." << std::endl;
    }
    else
    {
        std::cout << "SDL_Init() failed. Error code " << errorCode << ": " << SDL_GetError() << std::endl;
        system("pause");
        return errorCode;
    }

    // Attempt to create a maximized window that can be restored to a kWidthxkHeight, centered window.
    g_window = SDL_CreateWindow("Jewel James",            // title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  // x, y
        kWidth, kHeight,                                 // w, h
        0);                                              // flags
    if (g_window != nullptr)
    {
        std::cout << "SDL_CreateWindow() succeeded." << std::endl;
    }
    else
    {
        std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        system("pause");
        return -1;
    }

    // Attempts to create a hardware-accelerated renderer for our window.
    g_Renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_Renderer != nullptr)
    {
        std::cout << "SDL_CreateRenderer() succeeded." << std::endl;
    }
    else
    {
        std::cout << "SDL_CreateRenderer() failed. Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        system("pause");
        return -1;
    }
    std::cout << "Initialization successful!!!" << std::endl;

    StateManager::PushState(new TitleState());  // Push the TitleState onto the state stack

    g_keyState = SDL_GetKeyboardState(nullptr);  // Get the current keyboard state

    is_running = true;
    return 0;
}

bool Game::IsRunning()
{
    return is_running;
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_running = false;  // Quit the game loop if the window is closed
            break;
        }
    }
}

bool Game::KeyDown(SDL_Scancode key)
{
    if (g_keyState)
    {
        return g_keyState[key] == 1;  // Check if the specified key is currently pressed
    }
    return false;
}

void Game::Update(float deltaTime)
{
    StateManager::Update(deltaTime);  // Update the current state
}

void Game::Render()
{
    StateManager::Render();  // Render the current state
    SDL_RenderPresent(g_Renderer);  // Update the screen
}

void Game::Clean()
{
    std::cout << "Cleaning engine..." << std::endl;
    StateManager::Quit();  // Clean up the state manager
    SDL_DestroyRenderer(g_Renderer);  // Destroy the renderer
    SDL_DestroyWindow(g_window);  // Destroy the window
    SDL_Quit();  // Quit SDL

    delete this;  // Delete the Game instance
}
