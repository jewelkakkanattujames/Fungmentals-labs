#include "States.h"
#include "Game.h"
#include "StateManager.h"
#include "GameObject.h"
#include <iostream>
#include "CollisionManager.h"

// Begin TitleState
void TitleState::Enter()
{
	// Function called when entering the TitleState
	std::cout << "Entering TitleState..." << std::endl;
}

void TitleState::Update(float deltaTime)
{
	// Update logic for the TitleState
	timer += deltaTime;

	if (timer >= 4.0f)
	{
		// Transition to the MenuState after 4 seconds
		StateManager::ChangeState(new MenuState());
	}
}

void TitleState::Render()
{
	// Render logic for the TitleState
	std::cout << "Rendering TitleState..." << std::endl;
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void TitleState::Exit()
{
	// Function called when exiting the TitleState
	std::cout << "Exiting TitleState..." << std::endl;
}
// End TitleState


// Begin MenuState
void MenuState::Enter()
{
	// Function called when entering the MenuState
	std::cout << "Entering MenuState..." << std::endl;
}

void MenuState::Update(float deltaTime)
{
	// Update logic for the MenuState
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_C))
	{
		// Transition to the CreditState if 'C' key is pressed
		std::cout << "Changing to CreditState..." << std::endl;
		StateManager::ChangeState(new CreditState());
	}
	else if (GameInstance.KeyDown(SDL_SCANCODE_G))
	{
		// Push the GameState onto the state stack if 'G' key is pressed
		std::cout << "Changing to GameState..." << std::endl;
		StateManager::PushState(new GameState());
	}
}

void MenuState::Render()
{
	// Render logic for the MenuState
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 0, 128, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void MenuState::Exit()
{
	// Function called when exiting the MenuState
	std::cout << "Exiting MenuState..." << std::endl;
}
// End MenuState

// Begin CreditState
void CreditState::Enter()
{
	// Function called when entering the CreditState
	std::cout << "Entering CreditState..." << std::endl;
}

void CreditState::Update(float deltaTime)
{
	// Update logic for the CreditState
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_ESCAPE))
	{
		// Transition to the MenuState if 'ESC' key is pressed
		std::cout << "Changing to MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}

void CreditState::Render()
{
	// Render logic for the CreditState
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void CreditState::Exit()
{
	// Function called when exiting the CreditState
	std::cout << "Exiting CreditState..." << std::endl;
}
// End CreditState

// Begin GameState
void GameState::Enter()
{
	// Function called when entering the GameState
	std::cout << "Entering GameState..." << std::endl;

	// Generate random positions, sizes, and colors for squares
	for (int i = 0; i < 10; ++i)
	{
		int x = rand() % (Game::kWidth - 40); // Subtract the square width from the screen width
		int y = rand() % (Game::kHeight - 40); // Subtract the square height from the screen height
		int size = rand() % 50 + 20; // Random size between 20 and 70
		Uint8 r = rand() % 256; // Random value for red component (0-255)
		Uint8 g = rand() % 256; // Random value for green component (0-255)
		Uint8 b = rand() % 256; // Random value for blue component (0-255)

		m_gameObjects.push_back(new GameObject(x, y, size, size, r, g, b));
	}

	// Create the player object and add it to the gameObjects vector
	m_pPlayer = new GameObject(Game::kWidth / 2, Game::kHeight / 2, 100, 100, 255, 255, 255, 255);
	m_gameObjects.push_back(m_pPlayer);
	
}

void GameState::Update(float deltaTime)
{
	// Update logic for the GameState
	timer += deltaTime;

	if (timer >= 20.0f)
	{
		// Transition to the WinState after 20 seconds
		StateManager::ChangeState(new WinState());
	}

	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_P))
	{
		// Push the PauseState onto the state stack if 'P' key is pressed
		std::cout << "Changing to PauseState..." << std::endl;
		StateManager::PushState(new PauseState());
	}
	else
	{
		// Update player movement based on key inputs
		if (GameInstance.KeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->UpdatePositionY(-kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_S))
		{
			m_pPlayer->UpdatePositionY(kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->UpdatePositionX(-kPlayerSpeed * deltaTime);
		}
		if (GameInstance.KeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->UpdatePositionX(kPlayerSpeed * deltaTime);
		}

		// Checking for collision between the player object and other game objects
		for (GameObject* pObject : m_gameObjects)
		{
			if (pObject != m_pPlayer)
			{
				if (CollisionManager::AABBCheck(m_pPlayer->GetTransform(), pObject->GetTransform()))
				{
					// Push the LoseState onto the state stack if collision occurs
					std::cout << "Player Object Collision occured" << std::endl;
					StateManager::PushState(new LoseState());
				}
			}
		}
	}
}

void GameState::Render()
{
	// Render logic for the GameState
	SDL_Renderer* pRenderer = Game::GetInstance().GetRenderer();

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 150, 150);
	SDL_RenderClear(pRenderer);

	// Render all game objects in the gameObjects vector
	for (GameObject* pObject : m_gameObjects)
	{
		pObject->Draw(pRenderer);
	}
}

void GameState::Exit()
{
	// Function called when exiting the GameState
	std::cout << "Exiting GameState..." << std::endl;

	// Delete and clean up all game objects
	for (GameObject* pObject : m_gameObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
}

void GameState::Resume()
{
	// Function called when resuming the GameState
	std::cout << "Resuming GameState..." << std::endl;
}
// End GameState

// Begin PauseState
void PauseState::Enter()
{
	// Function called when entering the PauseState
	std::cout << "Entering PauseState..." << std::endl;
}

void PauseState::Update(float deltaTime)
{
	// Update logic for the PauseState
	if (Game::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE))
	{
		// Pop the current state from the state stack if 'ESC' key is pressed
		StateManager::PopState();
	}
}

void PauseState::Render()
{
	// Render logic for the PauseState
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 128, 128, 128, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Game::GetInstance().GetRenderer(), &rect);
}

void PauseState::Exit()
{
	// Function called when exiting the PauseState
	std::cout << "Exiting PauseState..." << std::endl;
}
// End PauseState

// Begin WinState
void WinState::Enter()
{
	// Function called when entering the WinState
	std::cout << "Entering WinState..." << std::endl;
}

void WinState::Update(float deltaTime)
{
	// Update logic for the WinState
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_SPACE))
	{
		// Transition to the MenuState if 'SPACE' key is pressed
		std::cout << "Changing to the MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}

void WinState::Render()
{
	// Render logic for the WinState
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 225, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void WinState::Exit()
{
	// Function called when exiting the WinState
	std::cout << "Exiting the WinState..." << std::endl;
}
// End WinState

// Begin LoseState
void LoseState::Enter()
{
	// Function called when entering the LoseState
	std::cout << "Entering the LoseState..." << std::endl;
}

void LoseState::Update(float deltaTime)
{
	// Update logic for the LoseState
	Game& GameInstance = Game::GetInstance();

	if (GameInstance.KeyDown(SDL_SCANCODE_SPACE))
	{
		// Transition to the MenuState if 'SPACE' key is pressed
		std::cout << "Changing to the MenuState..." << std::endl;
		StateManager::ChangeState(new MenuState());
	}
}

void LoseState::Render()
{
	// Render logic for the LoseState
	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 225, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance().GetRenderer());
}

void LoseState::Exit()
{
	// Function called when exiting the LoseState
	std::cout << "Exiting the LoseState..." << std::endl;
}
// End LoseState
