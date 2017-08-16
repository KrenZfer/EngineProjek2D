#pragma once
#include "MainGame.h"

int main(int argc, char *argv[]) {
	GameCore &mainGame = MainGame();
	mainGame.Run("TestEngine", 1280, 720, true);
	return 0;
}