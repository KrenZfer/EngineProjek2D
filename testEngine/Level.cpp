#include "Level.h"
#include <Graphic\ErrorHandling.h>
#include <ctime>

void Level::LoadLevel(const char * textPath)
{
	if (IOManager::readFiletoBuffer(textPath, &textLevel)) {
		string::iterator its = textLevel.begin();
		vector<char> row;
		for (; its != textLevel.end(); its++) {
			if (*its == '#') {
				ignore = true;
			}
			else if (*its == 'B' && !ignore) {
				row.emplace_back('B');
			}
			else if (*its == 'G' && !ignore) {
				row.emplace_back('G');
			}
			else if (*its == '\n') {
				if (ignore) {
					ignore = false;
				}
				else {
					parts.emplace_back(row);
					row = vector<char>();
				}
			}
		}
	}
	else {
		ErrorHandling::nonFatalError("Level text not found?!!");
	}

	int i = parts.size();
	int tempheight = i - 1;
	buildingstartX = 100.0f;
	buildingstartY = 0.0f;
	float widthTile = 128.0f;
	float heightTile = 128.0f;

	widthBuilding = parts[0].size() * widthTile;
	heightBuilding = i * heightTile;

	for (i = i - 1; i >= 0; i--) {
		float tempy = heightTile * (tempheight - i);
		int partsiSize = parts[i].size();
		for (int j = 0; j < partsiSize; j++) {

			Sprite temp;
			float tempx = widthTile * j;
			if (parts[i][j] == 'B') {
				temp.init(vec2(buildingstartX + tempx, tempy), vec2(1.0f), "Texture/brickWall.png", 4.0f);
				Walls.emplace_back(temp);
			}
			else if (parts[i][j] == 'G') {
				temp.init(vec2(buildingstartX + tempx, tempy), vec2(1.0f), "Texture/glass.png", 4.0f);
				Glasses.emplace_back(temp);
			}
		}
		glassInform.emplace_back(0);
	}

	vector<Glass>::iterator itg = Glasses.begin();
	while (spotNum > 0) {
		bool spot = false;
		srand((unsigned int)time(0)*spotNum);
		int rand = randGenerator(100);
		if (itg != Glasses.end()) {
			if (rand > 50 && !itg->getSpot()) {
				itg->setSpot(true);
				int indeks = static_cast<int>(itg->getPosition().y);
				glassInform[indeks / static_cast<int>(heightTile)]++;
				spotNum--;
			}
		}
		itg++;
		if (itg == Glasses.end()) {
			itg = Glasses.begin();
		}
	}
}

void Level::LoadTest(const char * textPath)
{
	if (IOManager::readFiletoBuffer(textPath, &textLevel)) {
	}
	else {
		ErrorHandling::nonFatalError("Level text not found\n!!!");
	}
}

void Level::init(const char * textPath, Camera *camera, InputManager *inputManager, int screenWidth, int screenHeight)
{
	counter = 1;
	l_screenWidth = screenWidth;
	l_screenHeight = screenHeight;
	l_camera = camera;
	player = new Player(vec2(100.0f, 100.0f), "Texture/mancharacter.png", 1.0f, l_camera, *inputManager);
	player->init();

	Sky_Background.init(vec2(0.0f), vec2(1.0f), "Texture/Sky_background.png", 0.0f);
	cityParalax0.init(vec2(0.0f), vec2(1.0f), "Texture/cityParalax0.png", 2.0f);
	trainAcc.init(vec2(0.0f), vec2(1.0f), "Texture/keretaapi.png", 1.0f);
	bottomBuilding.init(vec2(0.0f), vec2(1.0f), "Texture/bottomBuilding.png", 3.0f);
	topBuilding.init(vec2(0.0f), vec2(1.0f), "Texture/topBuilding.png", 3.0f);
	cityParalax1.init(vec2(0.0f), vec2(1.0f), "Texture/cityParalax1.png", 1.0f);
	cityParalax2.init(vec2(0.0f), vec2(1.0f), "Texture/cityParalax2.png", 0.0f);

	LoadLevel(textPath);

	player->setBoundary(vec4(90.0f, widthBuilding, -player->getKey().kf_height/4, heightBuilding - player->getKey().kf_height));
}

void Level::update(float deltaTime)
{
	counter++;
	Sky_Background.setPosition(
		vec2(l_camera->getPosition().x - l_camera->getScreenSize().x / 2.0f, l_camera->getPosition().y / (heightBuilding - 900) * Sky_Background.getSize().y - l_camera->getScreenSize().y / 2.0f)
	);
	cityParalax1.setPosition(
		vec2(l_camera->getPosition().x - l_camera->getScreenSize().x / 2.0f, l_camera->getPosition().y / (heightBuilding) * cityParalax1.getSize().y * 2 - l_camera->getScreenSize().y / 2.0f + 200.0f)
	);
	cityParalax2.setPosition(
		vec2(l_camera->getPosition().x - l_camera->getScreenSize().x / 2.0f, l_camera->getPosition().y / (heightBuilding) * cityParalax2.getSize().y * 2.3f - l_camera->getScreenSize().y / 2.0f + 250.0f)
	);
	cityParalax0.setPosition(
		vec2(l_camera->getPosition().x - l_camera->getScreenSize().x / 2.0f, l_camera->getPosition().y / (heightBuilding)* cityParalax0.getSize().y - l_camera->getScreenSize().y / 2.0f)
	);
	bottomBuilding.setPosition(
		vec2(buildingstartX - (bottomBuilding.getSize().x - widthBuilding)/2, -bottomBuilding.getSize().y + buildingstartY)
	);
	topBuilding.setPosition(
		vec2(buildingstartX - (topBuilding.getSize().x - widthBuilding)/2, heightBuilding)
	);
	l_camera->setPosition(player->getCenter());
	player->update(deltaTime);
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].update(deltaTime);
		player->checkUpdate(/*ini diisi dengan benda yang kemungkinan ditabrak*/
			&obstacles[i]
		);
		if (obstacles[i].getPosition().y < -400.0f) {
			obstacles.erase(obstacles.begin() + i);
		}
	}
	for (int i = 0; i < buffs.size(); i++) {
		buffs[i].update(deltaTime);
		player->checkUpdate(/*ini diisi dengan benda yang kemungkinan ditabrak*/
			&buffs[i]
		);
		if (buffs[i].getPosition().y < -400.0f) {
			buffs.erase(buffs.begin() + i);
		}
	}
	int temp = 0;
	int count = 0;
	for (int i = 0; i < Glasses.size(); i++) {
		Glasses[i].update(deltaTime);
		player->checkUpdate(/*ini diisi dengan benda yang kemungkinan ditabrak*/
			&Glasses[i]
		);
		//update information about spot
		if (temp != Glasses[i].getPosition().y) {
			glassInform[temp / 128] = count;
			temp = Glasses[i].getPosition().y;
			count = 0;
		}
		if (Glasses[i].getSpot()) {
			count++;
		}
	}
	if (counter >= 5000) {
		counter = 1;
	}
	generateObstacle(deltaTime);
	generatePowerBuff(deltaTime);
}



void Level::draw(SpriteBatch * batch)
{
	vector<Glass>::iterator itg = Glasses.begin();
	vector<Sprite>::iterator itw = Walls.begin();
	vector<Obstacle>::iterator itobs = obstacles.begin();
	vector<PowerBuff>::iterator itpbs = buffs.begin();
	while (itg != Glasses.end() || itw != Walls.end() || itobs != obstacles.end() || itpbs != buffs.end()) {
		if (itg != Glasses.end()){
			itg->draw(batch);
			itg++;
		}
		if (itw != Walls.end()) {
			itw->draw(*batch);
			itw++;
		}
		if (itobs != obstacles.end()) {
			itobs->draw(batch);
			itobs++;
		}
		if (itpbs != buffs.end()) {
			itpbs->draw(batch);
			itpbs++;
		}
	}
	Sky_Background.draw(*batch);
	bottomBuilding.draw(*batch);
	topBuilding.draw(*batch);
	cityParalax0.draw(*batch);
	cityParalax1.draw(*batch);
	cityParalax2.draw(*batch);

	player->draw(batch);
}

void Level::initShader(const char * vertexPath, const char * fragmentPath)
{
	l_program.BuildShader(vertexPath, fragmentPath);
}

void Level::generateObstacle(float deltaTime)
{
	srand((unsigned int)time(0) * deltaTime * 5);
	int rand = randGenerator(static_cast<int>(widthBuilding)) + buildingstartX;
	srand((unsigned int)time(0) * deltaTime * 3);
	int randGen = randGenerator(static_cast<int>(100));

	if (counter % 120 == 0) {
		if (randGen <= 50) {
			obstacles.emplace_back(vec2(static_cast<float>(rand), heightBuilding), Obstacle::COMPUTER);
		}

		if (randGen >= 51 && randGen <= 84) {
			obstacles.emplace_back(vec2(static_cast<float>(rand), heightBuilding), Obstacle::COUCH);
		}

		if (randGen >= 85 && randGen <= 100) {
			obstacles.emplace_back(vec2(static_cast<float>(rand), heightBuilding), Obstacle::CLOSET);
		}
	}
}

void Level::generatePowerBuff(float deltaTime)
{
	srand((unsigned int)time(0) * counter*7);
	int rand = randGenerator(static_cast<int>(widthBuilding))+buildingstartX;
	srand((unsigned int)time(0) * deltaTime*counter*8);
	int randGen = randGenerator(static_cast<int>(100));
	//cout << "Counter : " << counter << endl;
	if (counter % 300 == 0) {
		//cout << "Random Buffs : " << randGen << endl;
		//cout << "Random X Buffs : " << rand << endl;
		if (randGen <= 25) {
			buffs.emplace_back(PowerBuff::POWER_DOWN::ICE_CUBE, vec2(static_cast<float>(rand), heightBuilding));
		}
		if (randGen >= 26 && randGen <= 50) {
			//cout << "emang masuk kok" << endl;
			buffs.emplace_back(PowerBuff::POWER_DOWN::BEER, vec2(static_cast<float>(rand), heightBuilding));
		}
		if (randGen >= 51 && randGen <= 75) {
			//cout << "emang masuk kok" << endl;
			buffs.emplace_back(PowerBuff::POWER_UP::SODA, vec2(static_cast<float>(rand), heightBuilding));
		}
		if (randGen >= 76 && randGen <= 100) {
			//cout << "emang masuk kok" << endl;
			buffs.emplace_back(PowerBuff::POWER_UP::BURGER, vec2(static_cast<float>(rand), heightBuilding));
		}
	}
}
