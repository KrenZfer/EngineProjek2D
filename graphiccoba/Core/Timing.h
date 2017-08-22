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

		void Init(unsigned int _targetFrame, unsigned int _timeScale);

		void limitFPS();
		void calculateFPS();
		void printFPS();
		
		void setTimeScale(unsigned int _timeScale);
		float GetDeltaTime();

	private:
		unsigned int checkFrameRate(unsigned int _targetFrame);

		unsigned int targetFrameRate, lastFrame, last, _fps, fps, timeScale;
		float targetFrameTime;

	};

}

#endif // !_H_TIMING_H_
