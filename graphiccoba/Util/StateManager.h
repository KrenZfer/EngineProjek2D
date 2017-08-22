#ifndef _H_STATE_MANAGER_H_

#include <vector>

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

private:
	vector<State*> stateStack;
};

#endif // !_H_STATE_MANAGER_H_
