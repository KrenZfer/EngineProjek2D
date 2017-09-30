#include "MainMenu.h"

MainMenu::MainMenu(StateManager *_stateManager, Camera *camera, InputManager *inputManager, WindowManager *_window) : State(_stateManager)
{
	state_Camera = camera;
	state_Input = inputManager;
	window = _window;
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	state_Camera->setPosition(vec2(0.0f));
	Background.init(0.0f, 0.0f, 1.0f, "Texture/main_menu.png");
	BowlFish.init(-300.0f, -35.0f, 1.0f, "Texture/bowl_fish.png");
	btn_Start.init(-200.0f, 110.0f, 1.0f, "Texture/HUD/playbutton.png", 1.0f, state_Input, state_Camera, state_Camera->getScreenSize());
	//btn_Credit.init(0.0f, 0.0f, 1.0f, "Texture/credit.png", state_Input, state_Camera, state_Camera->getScreenSize());
	btn_Exit.init(250.0f, 200.0f, 1.0f, "Texture/HUD/exitbutton.png", 1.0f, state_Input, state_Camera, state_Camera->getScreenSize());

	Background.setPosition(vec2(-Background.getSize().x / 2, -Background.getSize().y / 2));

	bgEnvironment = ResourceManager::getAudioData("Audio/oggfile/bgEnvironment.ogg", true);
	bgMusic = ResourceManager::getAudioData("Audio/oggfile/bgMusic.ogg", true);

	buttonClick = ResourceManager::getAudioData("Audio/oggfile/buttonClick.ogg", false);
	buttonHover = ResourceManager::getAudioData("Audio/oggfile/buttonHover.ogg", false);

	bgMusic.setVolume(0.2f);
	bgEnvironment.Play();
	bgMusic.Play();

	playonHover = false;
	exitonHover = false;


	animBtn_Start.createKeyFrame(btn_Start.getSprite(), 1, 3);
	animBtn_Exit.createKeyFrame(btn_Exit.getSprite(), 1, 2);
	animFish.createKeyFrame(BowlFish, 1, 4, 150);
	currentKeyStart = animBtn_Start.getKeyFrameIndexBased(0);
	currentKeyExit = animBtn_Exit.getKeyFrameIndexBased(0);
	currentKeyFish = animFish.getKeyFrameIndexBased(0);

	btn_Start.update();
	btn_Exit.update();
	btn_Start.setButtonActive(true);
	btn_Exit.setButtonActive(true);
}

void MainMenu::CleanUp()
{
	bgMusic.Stop();
	bgEnvironment.Stop();
}

void MainMenu::Pause()
{
}

void MainMenu::Resume()
{
}

void MainMenu::HandleEvent()
{
	if (btn_Start.onClicked()) {
		buttonClick.Play();
		gameMenu = new GameMenu(stateManager, state_Camera, state_Input, window);
		stateManager->changeState(gameMenu);
		currentKeyStart = animBtn_Start.getKeyFrameIndexBased(2);
		btn_Start.setButtonActive(false);
	}else if (btn_Start.onHover()) {
		if (!playonHover) {
			buttonHover.Play();
			playonHover = true;
		}
		currentKeyStart = animBtn_Start.getKeyFrameIndexBased(1);
	}
	else {
		if (playonHover) {
			playonHover = false;
		}
		currentKeyStart = animBtn_Start.getKeyFrameIndexBased(0);
	}

	if (btn_Exit.onClicked()) {
		buttonClick.Play();
		currentKeyExit = animBtn_Exit.getKeyFrameIndexBased(1);
		SDL_Delay(1000);
		SDL_Quit();
		exit(0);
	}
	else if(btn_Exit.onHover()){
		if (!exitonHover) {
			buttonHover.Play();
			exitonHover = true;
		}
		currentKeyExit = animBtn_Exit.getKeyFrameIndexBased(1);
	}
	else {
		if (exitonHover) {
			exitonHover = false;
		}
		currentKeyExit = animBtn_Exit.getKeyFrameIndexBased(0);
	}
}

void MainMenu::Update(float deltaTime)
{
	HandleEvent();
	btn_Start.update();
	//btn_Credit.update();
	btn_Exit.update();
	currentKeyFish = animFish.getCurrentKeyFrame(deltaTime);
}

void MainMenu::Draw(SpriteBatch &batch)
{
	Background.draw(batch);
	BowlFish.draw(batch, vec4(currentKeyFish.kf_u, currentKeyFish.kf_v, currentKeyFish.kf_u2, currentKeyFish.kf_v2), currentKeyFish.kf_width, currentKeyFish.kf_height);
	btn_Start.draw(batch, vec4(currentKeyStart.kf_u, currentKeyStart.kf_v, currentKeyStart.kf_u2, currentKeyStart.kf_v2), currentKeyStart.kf_width, currentKeyStart.kf_height);
	//btn_Credit.draw(batch);
	btn_Exit.draw(batch, vec4(currentKeyExit.kf_u, currentKeyExit.kf_v, currentKeyExit.kf_u2, currentKeyExit.kf_v2), currentKeyExit.kf_width, currentKeyExit.kf_height);
}
