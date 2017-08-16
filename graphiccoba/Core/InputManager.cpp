#include "InputManager.h"
#include <iostream>


EngineProject2D::InputManager::InputManager()
{
}

EngineProject2D::InputManager::~InputManager()
{
}

void EngineProject2D::InputManager::PressKey(unsigned int keyID)
{
	keyMap[keyID] = true;
	cout << "masuk Key Pressed : " << keyMap[keyID] << endl;
}

void EngineProject2D::InputManager::ReleaseKey(unsigned int keyID)
{
	keyMap[keyID] = false;
	cout << "masuk Key Released : " << keyMap[keyID] << endl;
}

bool EngineProject2D::InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
		cout << "masuk isKeyPressed" << endl;
		return true;
	}
	return false;
}

bool EngineProject2D::InputManager::isKeyDown(unsigned int keyID)
{
	auto it = keyMap.find(keyID);

	if (it != keyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

bool EngineProject2D::InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = prevKeyMap.find(keyID);

	if (it != prevKeyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}
