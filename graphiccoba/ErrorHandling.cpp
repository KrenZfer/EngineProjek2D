#include "ErrorHandling.h"

void EngineProject2D::ErrorHandling::fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Hit Enter To Quit" << endl;
	int temp;
	cin >> temp;
	SDL_Quit();
	exit(1);
}
