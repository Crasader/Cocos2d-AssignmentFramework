#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_
#include "cocos2d.h"

using namespace cocos2d;

class InputManager
{
public:
	static InputManager& getInstance()
	{
		static InputManager Instance;
		return Instance;
	}
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	void Init();
	void Update(float dt);


private:
	InputManager();
	~InputManager();
	std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;
};



#endif