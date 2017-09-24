#ifndef _H_STATE_MANAGER_H_
#define _H_STATE_MANAGER_H_

#include <vector>
//#include "../Graphic/SpriteBatch.h"

using namespace std;

class State;

class StateManager
{

public:
	StateManager();
	~StateManager();

	void changeState(State* state);
	void pushState(State* state);
	void popState();

	vector<State*> getStateStack() { return stateStack; }

private:
	vector<State*> stateStack;
};

#endif // !_H_STATE_MANAGER_H_