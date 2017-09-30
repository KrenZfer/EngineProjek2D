#include "GameMenu.h"
#include "MainMenu.h"

GameMenu::GameMenu(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window) : State(_stateManager)
{
	Gamecamera = camera;
	winManager = _window;
	GameInput = inputManager;
}

GameMenu::~GameMenu()
{
}

void GameMenu::Init()
{
	Gamecamera->setPosition(vec2(0.0f));
	level1 = new Level();
	currentStatus = OnGame::PLAY;
	initLevel("Level/level1.txt", Gamecamera, GameInput, winManager->getScreenWidth(), winManager->getScreenHeight());

	BackgroundHitam.init(vec2(0.0f), vec2(1.0f), "Texture/backgroundHitam.png");
	loadingText.init(vec2(0.0f), vec2(1.0f), "Texture/loadingAnimation.png");
	animLoading.createKeyFrame(loadingText, 3, 4);
	loadingKey = animLoading.getCurrentKeyFrame(0.0f);
	fishBowl.init(vec2(0.0f), vec2(1.0f), "Texture/bowl_fish.png");
	animFish.createKeyFrame(fishBowl, 1, 4);
	fishKey = animFish.getCurrentKeyFrame(0.0f);

	bgEnvironment = ResourceManager::getAudioData("Audio/oggfile/bgEnvironment.ogg", true);
	bgMusic = ResourceManager::getAudioData("Audio/oggfile/bgMusic.ogg", true);

	bgMusic.setVolume(0.2f);
	bgEnvironment.Play();
	bgMusic.Play();

	btnClick = ResourceManager::getAudioData("Audio/oggfile/buttonClick.ogg", false);
	btnHover = ResourceManager::getAudioData("Audio/oggfile/buttonHover.ogg", false);

	winSound = ResourceManager::getAudioData("Audio/oggfile/Win.ogg", false);
	loseSound = ResourceManager::getAudioData("Audio/oggfile/GameOver.ogg", false);

	onceTime = true;
	pauseonHover = false;
	continueonHover = false;
	homeonHover = false;
	restartonHover = false;
	statusChange = false;
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
	bgEnvironment.Stop();
	bgMusic.Stop();
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
	if (currentStatus == OnGame::PLAY) {
		if (HUD_PAUSE.onClicked()) {
			btnClick.Play();
			Pause();
		}
		if (HUD_PAUSE.onHover()) {
			if (!pauseonHover) {
				btnHover.Play();
				pauseonHover = true;
			}
		}
		else {
			if (pauseonHover) {
				pauseonHover = false;
			}
		}
	}

	if (currentStatus == OnGame::PAUSE || currentStatus == OnGame::LOSE || currentStatus == OnGame::WIN) {
		if (BTN_HOME.onClicked()) {
			btnClick.Play();
			mainMenu = MainMenu::instance(stateManager, Gamecamera, GameInput, winManager);
			stateManager->changeState(mainMenu);
		}
		if (BTN_HOME.onHover()) {
			if (!homeonHover) {
				btnHover.Play();
				homeonHover = true;
			}
		}
		else {
			if (homeonHover) {
				homeonHover = false;
			}
		}

		if (currentStatus == OnGame::PAUSE) {
			if (BTN_CONTINUE.onClicked()) {
				btnClick.Play();
				Resume();
			}
			if (BTN_CONTINUE.onHover()) {
				if (!continueonHover) {
					btnHover.Play();
					continueonHover = true;
				}
			}
			else {
				if (continueonHover) {
					continueonHover = false;
				}
			}
		}

		if (currentStatus == OnGame::LOSE) {
			if (BTN_RESTART.onClicked()) {
				btnClick.Play();
				gameMenu = new GameMenu(stateManager, Gamecamera, GameInput, winManager);
				stateManager->changeState(gameMenu);
			}
			if (BTN_RESTART.onHover()) {
				if (!restartonHover) {
					btnHover.Play();
					restartonHover = true;
				}
			}
			else {
				if (restartonHover) {
					restartonHover = false;
				}
			}
		}
	}
}

void GameMenu::Update(float deltaTime)
{
	if (!level1->getisLoadDone()) {
		level1->randomSpotPlace();
		BackgroundHitam.setPosition(
			vec2(-BackgroundHitam.getSize().x / 2, -BackgroundHitam.getSize().y / 2)
		);
		fishBowl.setPosition(
			vec2(-fishBowl.getSize().x/2, -fishBowl.getSize().y/2)
		);
		loadingText.setPosition(
			vec2(Gamecamera->getScreenSize().x/2 - loadingText.getSize().x, -Gamecamera->getScreenSize().y / 2 + loadingText.getSize().y)
		);
		fishKey = animFish.getCurrentKeyFrame(deltaTime);
		loadingKey = animLoading.getCurrentKeyFrame(deltaTime);
	}
	else {
		if (onceTime) {
			initHUD();
			counterSpot = -1;
			onceTime = false;
		}

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
			if (!statusChange) {
				loseSound.Play();
				statusChange = true;
			}
			currentStatus = OnGame::LOSE;
		}

		if (counterSpot == 0) {
			if (!statusChange) {
				winSound.Play();
				statusChange = true;
			}
			currentStatus = OnGame::WIN;
		}

		if (currentStatus == OnGame::PLAY) {
			level1->update(deltaTime);
		}
	}
}

void GameMenu::Draw(SpriteBatch &batch)
{
	if (!level1->getisLoadDone()) {
		BackgroundHitam.draw(batch);
		fishBowl.draw(batch, vec4(fishKey.kf_u, fishKey.kf_v, fishKey.kf_u2, fishKey.kf_v2), fishKey.kf_width, fishKey.kf_height);
		loadingText.draw(batch, vec4(loadingKey.kf_u, loadingKey.kf_v, loadingKey.kf_u2, loadingKey.kf_v2), loadingKey.kf_width, loadingKey.kf_height);
	}
	else {
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
}

void GameMenu::initLevel(const char * _levelPath, Camera * camera, InputManager * inputManager, int screenWidth, int screenHeight)
{
	level1->init(_levelPath, camera, inputManager, screenWidth, screenHeight);
}

