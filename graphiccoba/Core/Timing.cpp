#include "Timing.h"
#include <iostream>



EngineProject2D::Timing::Timing()
{
}

void EngineProject2D::Timing::Init(unsigned int _targetFrame, unsigned int _timeScale)
{
	targetFrameRate = checkFrameRate(_targetFrame);
	targetFrameTime = 1000.0f / targetFrameRate;

	last = SDL_GetTicks();
	timeScale = _timeScale;
	lastFrame = 0;
}

void EngineProject2D::Timing::setTimeScale(unsigned int _timeScale) {
	timeScale = _timeScale;
}

float EngineProject2D::Timing::GetDeltaTime()
{
	unsigned int time = SDL_GetTicks();
	unsigned int delta = time - lastFrame;
	lastFrame = time;

	return delta * timeScale;
}

void EngineProject2D::Timing::limitFPS()
{
	//std::cout << "targetframetime : " << targetFrameTime << std::endl;
	SDL_Delay((Uint32)(targetFrameTime));
}

void EngineProject2D::Timing::calculateFPS()
{
	if (SDL_GetTicks() - last > 1000) {
		fps = _fps;
		_fps = 0;
		last += 1000;
	}
	_fps++;
}

void EngineProject2D::Timing::printFPS()
{
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 60) {
		std::cout << "FPS: " << fps << std::endl;
		frameCounter = 0;
	}
}

unsigned int EngineProject2D::Timing::checkFrameRate(unsigned int _targetFrame)
{
	if (_targetFrame >= 0) {
		return _targetFrame;
	}
	else {
		return 60;
	}
}


