#include <iostream>
#include <chrono>
#include "Game.h"

int main(int argc, char* argv[])
{
    // Create an instance of the game
    Game& myGameInstance = Game::GetInstance();

    // Initialize the game window and resources
    int result = myGameInstance.Init("Jewel James", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (result == 0)
    {
        // Allocate a time_point outside the loop to store the time of the last frame
        auto lastFrameTime = std::chrono::high_resolution_clock::now();

        while (myGameInstance.IsRunning())
        {
            // Get the current time_point
            auto thisFrameTime = std::chrono::high_resolution_clock::now();

            // Calculate the duration of the last frame
            std::chrono::duration<float> lastFrameDuration = thisFrameTime - lastFrameTime;

            // Convert the duration to a float representing the time in seconds
            float deltaTime = lastFrameDuration.count();

            // Update the last frame time with the current frame time
            lastFrameTime = thisFrameTime;

            // Handle user events (input)
            myGameInstance.HandleEvents();

            // Update the game logic and entities using the elapsed time (deltaTime)
            myGameInstance.Update(deltaTime);

            // Render the game to the screen
            myGameInstance.Render();
        }

        // Clean up and release resources
        myGameInstance.Clean();
    }

    return result;
}
