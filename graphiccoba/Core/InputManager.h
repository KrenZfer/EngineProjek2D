#ifndef _H_INPUT_MANAGER_H_
#define _H_INPUT_MANAGER_H_

#include <unordered_map>
#include <GLM\glm.hpp>

using namespace std;

namespace EngineProject2D {

	class InputManager {
	
	public:
		InputManager();
		~InputManager();

		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);
		bool isKeyDown(unsigned int keyID);
	
	private:
		bool wasKeyDown(unsigned int keyID);
		unordered_map<unsigned int, bool> keyMap;
		unordered_map<unsigned int, bool> prevKeyMap;
	};
}

#endif