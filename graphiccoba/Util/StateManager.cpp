#include "StateManager.h"
#include "State.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::changeState(State * state)
{
	if (!stateStack.empty()) {
		stateStack.back()->CleanUp();
		stateStack.pop_back();
	}

	stateStack.push_back(state);
	stateStack.back()->Init();
}
//gsm->pushState(new State(gsm));
void StateManager::pushState(State * state)
{
	if (!stateStack.empty()) {
		stateStack.back()->Pause();
	}
	
	stateStack.push_back(state);
	stateStack.back()->Init();
}

void StateManager::popState()
{
	if (!stateStack.empty()) {
		stateStack.back()->CleanUp();
		stateStack.pop_back();
	}

	if (!stateStack.empty()) {
		stateStack.back()->Resume();
	}

}
