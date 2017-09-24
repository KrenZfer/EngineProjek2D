#ifndef _H_STATE_H_

#define _H_STATE_H_

#include "../Graphic/SpriteBatch.h"

class StateManager;

using namespace EngineProject2D;

class State
{

public:
	State() {}
	State(StateManager* _stateManager) { stateManager = _stateManager; }
	
	virtual void Init() = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	
	virtual void HandleEvent() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteBatch &batch) = 0;

protected:
	StateManager *stateManager;
};

#endif // !_H_STATE_H_
