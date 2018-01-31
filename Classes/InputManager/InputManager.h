#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_
#include "cocos2d.h"
#include "GenericManager.h"
using namespace cocos2d;

class InputManager
{
	typedef std::function<void()> fp;
public:
	SINGLETON_CLASS(InputManager)

	virtual void Init();
	virtual void Update(float dt);

	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode, bool seconds);

	virtual void onMouseMove(Event*);
	virtual void onMouseUp(Event*);
	virtual void onMouseDown(Event*);
	virtual void onMouseScroll(Event*);

public:
	//vector<fp> m_onKeyPress_EventMap;
	//vector<fp> m_onKeyRelease_EventListMap;
	//vector<fp> m_onKeyHold_EventListMap;
private:
	InputManager();
	~InputManager();
	std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;
};



#endif