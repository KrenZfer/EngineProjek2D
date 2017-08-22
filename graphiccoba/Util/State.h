#ifndef _H_STATE_H_

class StateManager;

class State
{

public:
	virtual void Init() = 0;
	virtual void CleanUp() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	
	virtual void HandleEvent() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	State();
	State(StateManager* _stateManager);

private:
	StateManager stateManager;
};

#endif // !_H_STATE_H_
