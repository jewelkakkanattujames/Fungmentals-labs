#include "StateManager.h"
#include "States.h"

std::vector<State*> StateManager::s_states;

// Update the current state
void StateManager::Update(float deltaTime)
{
	if (!s_states.empty())
	{
		// s_states.back() represents the current state, by pointer
		s_states.back()->Update(deltaTime);
	}
}

// Render the current state
void StateManager::Render()
{
	if (!s_states.empty())
	{
		s_states.back()->Render();
	}
}

// Push a new state onto the state stack
void StateManager::PushState(State* pState)
{
	s_states.push_back(pState);
	s_states.back()->Enter();
}

// Pop the top state from the state stack
void StateManager::PopState()
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.pop_back();
	}

	if (!s_states.empty())
		s_states.back()->Resume();
}


// Change the current state to a new state
void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.pop_back();
	}

	s_states.push_back(pState);
	s_states.back()->Enter();
}


// Quit the state manager and clean up all states
void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

// Get a reference to the vector of states
std::vector<State*>& StateManager::GetStates()
{
	return s_states;
}
