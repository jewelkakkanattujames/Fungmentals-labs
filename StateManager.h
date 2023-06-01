#pragma once

#include <vector>  // Include the vector library for vector container

class State;  // Forward declaration of the State class

class StateManager
{
private: // Public properties

    static std::vector<State*> s_states;  // Static vector to hold pointers to State objects

public: // Public methods

    // Update all states in the state stack
    static void Update(float deltaTime);

    // Render all states in the state stack
    static void Render();

    // Push a state onto the state stack
    static void PushState(State* pState);  // Used when going to PauseState

    // Pop the top state from the state stack
    static void PopState();  // Used when leaving PauseState

    // Change the current state to a new state
    static void ChangeState(State* pState);

    // Perform cleanup and quit the state manager
    static void Quit();

    // Get a reference to the vector of state pointers
    static std::vector<State*>& GetStates();

private: //Private methods

    // Private constructor to prevent instances of StateManager from being created
    StateManager() {}

};
