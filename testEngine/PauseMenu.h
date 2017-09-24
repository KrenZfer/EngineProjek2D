#ifndef _H_PAUSE_MENU_H_
#define _H_PAUSE_MENU_H_

#include <Util\State.h>
#include <Util\StateManager.h>
#include <Graphic\Camera.h>
#include <Core\InputManager.h>
#include <Graphic\WindowManager.h>
#include <Graphic\UI\button.h>

class PauseMenu : public State {

public:
	PauseMenu(StateManager *stateManager, Camera *camera, InputManager *inputManager, WindowManager *winManager);
	~PauseMenu();

	void Init() override;
	void CleanUp() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent() override;
	void Update(float deltaTime) override;
	void Draw(SpriteBatch &batch) override;

	static PauseMenu* instance(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *winManager) {
		if (pauseInstance == NULL) {
			pauseInstance = new PauseMenu(_stateManager, camera, inputManager, winManager);
		}
		return pauseInstance;
	}

private:
	Button HOME;
	Button CONTINUE;
	Sprite Background;

	static PauseMenu *pauseInstance;


};



#endif // !_H_PAUSE_MENU_H_

