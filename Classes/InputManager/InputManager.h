#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_
#include "cocos2d.h"
#include "GenericManager.h"
using namespace cocos2d;

class InputManager : GenericManager
{
public:
	SINGLETON_CLASS(InputManager)

	virtual void Init();
	virtual void Update(float dt);

	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	void onKeyReleased(EventKeyboard::KeyCode, Event*);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode, bool seconds);

	void onMouseMove(Event*);
	void onMouseUp(Event*);
	void onMouseDown(Event*);
	void onMouseScroll(Event*);
private:
	InputManager();
	~InputManager();
	std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;
};



#endif