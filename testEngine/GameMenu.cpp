#include "GameMenu.h"
#include "MainMenu.h"

GameMenu::GameMenu(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window) : State(_stateManager)
{
	Gamecamera = camera;
	winManager = _window;
	GameInput = inputManager;
	level1 = new Level();
}

GameMenu::~GameMenu()
{
}

void GameMenu::Init()
{
	level1 = new Level();
	currentStatus = OnGame::PLAY;
	initLevel("Level/level1.txt", Gamecamera, GameInput, winManager->getScreenWidth(), winManager->getScreenHeight());

	initHUD();

	counterSpot = -1;
}

void GameMenu::initHUD()
{
	HUD_HP.init(0.0f, 0.0f, 1.0f, "Texture/HUD/HUD_HP.png", 9.0f);
	HUD_PAUSE.init(0.0f, 0.0f, 1.0f, "Texture/HUD/HUD_PAUSE.png", 10.0f, GameInput, Gamecamera, Gamecamera->getScreenSize());
	HUD_MINI_MAP.init(0.0f, 0.0f, 1.0f, "Texture/HUD/HUD_MINI_MAP.png", 9.0f);
	HUD_Player_Pointer.init(0.0f, 0.0f, 1.0f, "Texture/HUD/HUD_PLAYER_POINTER.png", 11.0f);
	HUD_Player_Pointer.setSize(27, 27);

	BTN_CONTINUE = Button("CONTINUE");

	BTN_HOME.init(0.0f, 0.0f, 1.0f, "Texture/HUD/BUTTON_HOME.png", 15.0f, GameInput, Gamecamera, Gamecamera->getScreenSize());
	BTN_CONTINUE.init(0.0f, 0.0f, 1.0f, "Texture/HUD/BUTTON_CONTINUE.png", 15.0f, GameInput, Gamecamera, Gamecamera->getScreenSize());
	BTN_RESTART.init(0.0f, 0.0f, 1.0f, "Texture/HUD/BUTTON_RESTART.png", 15.0f, GameInput, Gamecamera, Gamecamera->getScreenSize());
	BACKGROUND.init(0.0f, 0.0f, 1.0f, "Texture/HUD/BACKGROUND_PAUSE.png", 12.0f);

	health_num = level1->getPlayer()->getPlayerHealth();
	Sprite temp;
	for (int i = 0; i < health_num; i++) {
		temp.init(vec2(0.0f), vec2(1.0f), "Texture/HUD/HUD_HEART.png", 10.0f);
		HUD_HP_ICON.emplace_back(temp);
	}
	// 27 x 395
	heightBuilding = level1->getBuildingHeight();
	glassInformation = level1->getGlassInformation();
	temp.init(0.0f, 0.0f, 1.0f, "Texture/HUD/HUD_SPOT_POINTER.png", 10.0f);
	for (int i = 0; i < glassInformation.size(); i++) {
		temp.setSize(22, 395 / glassInformation.size());
		HUD_Spot_Pointer.emplace_back(temp);
	}
}


void GameMenu::CleanUp()
{
	//HUD_Spot_Pointer.clear();
	//glassInformation.clear();
	//HUD_HP_ICON.clear();
	//health_num = 0;
	//delete level1;
}

void GameMenu::Pause()
{
	currentStatus = OnGame::PAUSE;
}

void GameMenu::Resume()
{
	BTN_CONTINUE.setButtonActive(false);
	BTN_RESTART.setButtonActive(false);
	BTN_HOME.setButtonActive(false);
	currentStatus = OnGame::PLAY;
}

void GameMenu::HandleEvent()
{
	if (HUD_PAUSE.onClicked() && currentStatus == OnGame::PLAY) {
		Pause();
	}
	//HUD_PAUSE.onHover();
	//BTN_CONTINUE.onHover();
	if (currentStatus == OnGame::PAUSE || currentStatus == OnGame::LOSE || currentStatus == OnGame::WIN) {
		if (BTN_HOME.onClicked()) {
			mainMenu = MainMenu::instance(stateManager, Gamecamera, GameInput, winManager);
			stateManager->changeState(mainMenu);
		}

		if (BTN_CONTINUE.onClicked() && currentStatus == OnGame::PAUSE) {
			Resume();
		}

		if (BTN_RESTART.onClicked() && currentStatus == OnGame::LOSE) {
			gameMenu = new GameMenu(stateManager, Gamecamera, GameInput, winManager);
			stateManager->changeState(gameMenu);
		}
	}
}

void GameMenu::Update(float deltaTime)
{
	HandleEvent();
	
	//HUD HP PART
	HUD_HP.setPosition(vec2(
		-Gamecamera->getScreenSize().x / 2 + Gamecamera->getPosition().x,
		Gamecamera->getScreenSize().y / 2 - HUD_HP.getSize().y + Gamecamera->getPosition().y));
	for (int i = 0; i < health_num; i++) {
		HUD_HP_ICON[i].setPosition(vec2(HUD_HP.getPosition().x + (HUD_HP_ICON[i].getSize().x * i) + 50.0f, HUD_HP.getPosition().y + 3.0f));
	}

	//HUD PAUSE PART
	HUD_PAUSE.update();
	HUD_PAUSE.setPosition(vec2(Gamecamera->getScreenSize().x / 2 + Gamecamera->getPosition().x - HUD_PAUSE.getSprite().getSize().x, Gamecamera->getScreenSize().y / 2 - HUD_HP.getSize().y + Gamecamera->getPosition().y));

	//MINI MAP PART
	glassInformation = level1->getGlassInformation();
	HUD_MINI_MAP.setPosition(vec2(Gamecamera->getScreenSize().x / 2 - HUD_MINI_MAP.getSize().x - 20.0f + Gamecamera->getPosition().x, -HUD_MINI_MAP.getSize().y / 2.0f + Gamecamera->getPosition().y));
	HUD_Player_Pointer.setPosition(vec2(HUD_MINI_MAP.getPosition().x + 2.5f, HUD_MINI_MAP.getPosition().y + 5 + (Gamecamera->getPosition().y / heightBuilding*height_mini_map)));
	health_num = level1->getPlayer()->getPlayerHealth();
	
	for (int i = 0; i < HUD_Spot_Pointer.size(); i++) {
		HUD_Spot_Pointer[i].setPosition(vec2(HUD_MINI_MAP.getPosition().x + 5.0f, HUD_MINI_MAP.getPosition().y + 5 + (i * 27)));
	}

	//MENU WHEN PAUSE AND PLAYER DIE
	BTN_HOME.setPosition(vec2(
		-BTN_HOME.getSprite().getSize().x / 2 + Gamecamera->getPosition().x, BTN_HOME.getSprite().getSize().y / 2 + Gamecamera->getPosition().y
	));
	BTN_HOME.update();
	BTN_CONTINUE.setPosition(vec2(
		-BTN_CONTINUE.getSprite().getSize().x / 2 + Gamecamera->getPosition().x, -BTN_CONTINUE.getSprite().getSize().y + Gamecamera->getPosition().y + 5
	));
	BTN_CONTINUE.update();
	BTN_RESTART.setPosition(vec2(
		-BTN_RESTART.getSprite().getSize().x / 2 + Gamecamera->getPosition().x, -BTN_RESTART.getSprite().getSize().y + Gamecamera->getPosition().y + 5
	));
	BTN_RESTART.update();
	BACKGROUND.setPosition(-BACKGROUND.getSize() / 2.0f + Gamecamera->getPosition());

	//CHECK GAME STATE FOR ACTIVATE BUTTON
	if (currentStatus == OnGame::PAUSE || currentStatus == OnGame::LOSE) {
		BTN_HOME.setButtonActive(true);
		if (currentStatus == OnGame::PAUSE) {
			BTN_CONTINUE.setButtonActive(true);
		}
		if (currentStatus == OnGame::LOSE) {
			BTN_RESTART.setButtonActive(true);
		}
	}
	//CHECK IF PLAYER DIE
	if (level1->getPlayer()->getPlayerStatus() == Player::DEAD) {
		currentStatus = OnGame::LOSE;
	}

	if (counterSpot == 0) {
		currentStatus = OnGame::WIN;
	}

	if (currentStatus == OnGame::PLAY) {
		level1->update(deltaTime);
	}
}

void GameMenu::Draw(SpriteBatch &batch)
{
	level1->draw(&batch);
	for (int i = 0; i < health_num; i++) {
		HUD_HP_ICON[i].draw(batch);
	}
	HUD_HP.draw(batch);
	HUD_PAUSE.draw(batch);
	HUD_MINI_MAP.draw(batch);
	HUD_Player_Pointer.draw(batch);
	if (currentStatus == OnGame::PAUSE || currentStatus == OnGame::LOSE || currentStatus == OnGame::WIN) {
		BTN_HOME.draw(batch);
		BACKGROUND.draw(batch);
		if (currentStatus == OnGame::PAUSE) {
			BTN_CONTINUE.draw(batch);
		}
		if (currentStatus == OnGame::LOSE) {
			BTN_RESTART.draw(batch);
		}
	}
	counterSpot = 0;
	for (int i = 0; i < HUD_Spot_Pointer.size(); i++) {
		if (glassInformation[i] > 0) {
			counterSpot++;
			HUD_Spot_Pointer[i].draw(batch);
		}
	}
}

void GameMenu::initLevel(const char * _levelPath, Camera * camera, InputManager * inputManager, int screenWidth, int screenHeight)
{
	level1->init(_levelPath, camera, inputManager, screenWidth, screenHeight);
}

