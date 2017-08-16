#ifndef _H_TIMING_H_
#define _H_TIMING_H_

#include <SDL\SDL.h>
#include <iostream>
#include <string>
#include <stdlib.h>

namespace EngineProject2D {

	class Timing {

	public:
		Timing();

		void init(unsigned int _targetFrame, unsigned int _timeScale);
		void update();
		
		void setTimeScale(unsigned int _timeScale);
		float GetDeltaTime();

	private:
		void limitFPS();
		void calculateFPS();
		void printFPS();
		unsigned int checkFrameRate(unsigned int _targetFrame);

		unsigned int targetFrameRate, lastFrame, last, _fps, fps, timeScale;
		float targetFrameTime;

	};

}

#endif // !_H_TIMING_H_
