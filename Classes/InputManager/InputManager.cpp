#include "InputManager.h"
#include "SceneManager.h"
#include "MasterManager.h"

InputManager::InputManager()
{
	MASTERMANAGER_CALLBACK_INIT_FUNC(InputManager, Init)
	MASTERMANAGER_CALLBACK_UPDATE_FUNC(InputManager, Update)

	CCLOG("Input Manager Init");
}

InputManager::~InputManager()
{
}

void InputManager::Init()
{
	Key_map.clear();

	//SceneManager::getInstance().get_current_scene()->addChild(this);

	auto k_listener = EventListenerKeyboard::create();
	//k_listener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	//k_listener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	k_listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		InputManager::getInstance().onKeyPressed(keyCode, event);
	};
	k_listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		InputManager::getInstance().onKeyReleased(keyCode, event);
	};
	SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(k_listener, SceneManager::getInstance().get_current_scene());

	//auto m_listener = EventListenerMouse::create();
	//m_listener->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	//m_listener->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);
	//m_listener->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	//m_listener->onMouseScroll = CC_CALLBACK_1(InputManager::onMouseScroll, this);
	//SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, SceneManager::getInstance().get_current_scene());

	//auto t_listener = EventListenerTouchOneByOne::create();
	//t_listener->onTouchBegan = [](Touch* touch, Event* event) {
	//	//type your code for the callback function here
	//	return true;
	//};
	//t_listener->onTouchMoved = [](Touch* touch, Event* event) {
	//	//type your code for the callback function here
	//	return true;
	//};
	//t_listener->onTouchEnded = [](Touch* touch, Event* event) {
	//	//type your code for the callback function here
	//	return true;
	//};
	//SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(t_listener, this);
}

void InputManager::Update(float dt)
{
 	if (isKeyPressed(EventKeyboard::KeyCode::KEY_BACK_SLASH))
		int test = 0;
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (Key_map.find(keyCode) == Key_map.end()) {
		Key_map[keyCode] = std::chrono::high_resolution_clock::now();
	}

}
void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Key_map.erase(keyCode);
}
bool InputManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode code)
{
	if (Key_map.find(code) != Key_map.end())
		return true;
	return false;
}

double InputManager::keyPressedDuration(EventKeyboard::KeyCode code, bool seconds)
{
	if (!isKeyPressed(code))
		return 0;  // Not pressed, so no duration 

				   // Return the amount of time that has elapsed between now and when the user
				   // first started holding down the key in milliseconds
				   // Obviously the start time is the value we hold in our std::map Key_map
	if (seconds)
		return (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - Key_map[code]).count()) * 0.001f;
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - Key_map[code]).count();
}

void InputManager::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	e->getCursorX();
}
void InputManager::onMouseUp(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
void InputManager::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
void InputManager::onMouseScroll(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}