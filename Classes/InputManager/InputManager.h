#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_
#include "cocos2d.h"
#include "GenericManager.h"
using namespace cocos2d;

class InputManager
{
public:
	//typedef std::function<void(Event*)> functionpt;
	typedef void(*functionpt)(EventKeyboard::KeyCode, Event*);
	SINGLETON_CLASS(InputManager)

	virtual void Init();
	virtual void Update(float dt);
	//Keyboard
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode, bool seconds);
	//Mouse
	virtual void onMouseMove(Event*);
	virtual void onMouseUp(Event*);
	virtual void onMouseDown(Event*);
	virtual void onMouseScroll(Event*);

	bool isMouseDown();

	void afterScreenCapture(bool somebool, const std::string& somestring);
public:
	std::vector<functionpt> m_onKeyPress_EventMap;
	std::vector<functionpt> m_onKeyRelease_EventListMap;
private:
	InputManager();
	~InputManager();
	std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> Key_map;

	bool m_mousedown;
};



#endif