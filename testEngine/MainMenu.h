#ifndef _H_MAIN_MENNU_H_
#define _H_MAIN_MENNU_H_

#include <Util\State.h>
#include <Util\StateManager.h>
#include <Graphic\UI\button.h>
#include <Core\InputManager.h>
#include <Graphic\Camera.h>

#include "GameMenu.h"
#include "CreditMenu.h"

class MainMenu : public State
{
public:
	MainMenu(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window);
	~MainMenu();

	void Init() override;
	void CleanUp() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent() override;
	void Update(float deltaTime) override;
	void Draw(SpriteBatch &batch) override;

	static MainMenu* instance(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window) {
		if(menuInstance == NULL){
			menuInstance = new MainMenu(_stateManager, camera, inputManager, _window);
		}
		return menuInstance;
	}

private:
	static MainMenu *menuInstance;
	Button btn_Start;
	Button btn_Credit;
	Button btn_Exit;
	Sprite Background;
	Sprite BowlFish;
	Animation animFish;
	Animation animBtn_Start;
	Animation animBtn_Exit;
	KeyFrame currentKeyStart;
	KeyFrame currentKeyExit;
	KeyFrame currentKeyFish;
	Camera *state_Camera;
	InputManager *state_Input;
	WindowManager *window;
	GameMenu *gameMenu;
};

#endif // !_H_MAIN_MENNU_H_
