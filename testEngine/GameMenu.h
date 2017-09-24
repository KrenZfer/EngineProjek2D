#ifndef _H_GAME_MENU_H_
#define _H_GAME_MENU_H_

#include <Util\State.h>
#include <Util\StateManager.h>
#include "Level.h"

class MainMenu;

class GameMenu : public State
{
public:

	enum OnGame {PLAY, LOSE, PAUSE, WIN};

	GameMenu(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window);
	~GameMenu();

	void Init() override;
	void CleanUp() override;

	void Pause() override;
	void Resume() override;

	void HandleEvent() override;
	void Update(float deltaTime) override;
	void Draw(SpriteBatch &batch) override;

	void initLevel(const char* _levelPath, Camera *camera, InputManager *inputManager, int screenWidth, int screenHeight);

	//static GameMenu* instance(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window) {
	//	if (gameInstance == NULL) {
	//		gameInstance = new GameMenu(_stateManager, camera, inputManager, _window);
	//	}
	//	return gameInstance;
	//}

private:
	void initHUD();
	//static 
	GameMenu *gameInstance;
	Level *level1;
	const char* levelPath;
	Camera *Gamecamera;
	Camera HUD_Camera;

	int health_num;
	int height_mini_map = 395;
	int heightBuilding;
	int counterSpot;

	SpriteBatch HUD_Batch;
	GLSLProgram HUD_Program;

	OnGame currentStatus;

	//HUD NEED
	Sprite HUD_HP;
	vector<Sprite> HUD_HP_ICON;
	Button HUD_PAUSE;
	Sprite HUD_MINI_MAP;
	Sprite HUD_Player_Pointer;
	vector<Sprite> HUD_Spot_Pointer;
	vector<int> glassInformation;
	//PAUSE
	Button BTN_CONTINUE;
	Button BTN_HOME;
	Button BTN_RESTART;
	Sprite BACKGROUND;

	GameMenu *gameMenu;
	MainMenu *mainMenu;

	InputManager *GameInput;
	WindowManager *winManager;
};

#endif // !_H_GAME_MENU_H_

