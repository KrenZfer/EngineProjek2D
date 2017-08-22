#pragma once
#include "MainGame.h"

int main(int argc, char *argv[]) {
	GameCore &mainGame = MainGame();
	mainGame.Run("TestEngine", 800, 600, true);
	return 0;
}