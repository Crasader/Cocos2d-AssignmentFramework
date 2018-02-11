#include "InputManager.h"
#include "SceneManager.h"
#include "MasterManager.h"

InputManager::InputManager() :
	m_mousedown(false)
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

	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	/*k_listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		InputManager::getInstance().onKeyPressed(keyCode, event);
	};
	k_listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		InputManager::getInstance().onKeyReleased(keyCode, event);
	};*/
	SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(k_listener, SceneManager::getInstance().get_current_scene());

	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseDown = std::bind(&InputManager::onMouseDown, this, std::placeholders::_1);

	SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, SceneManager::getInstance().get_current_scene());

	//screencap testing
	m_onKeyPress_EventMap.push_back([](EventKeyboard::KeyCode keyCode, Event* event) {
		
		if (keyCode == EventKeyboard::KeyCode::KEY_M)
		{
			InputManager* instance = &InputManager::getInstance();
			utils::captureScreen(std::bind(&InputManager::afterScreenCapture, instance, std::placeholders::_1, std::placeholders::_2), "testcapture.png");
		}
	});
}

void InputManager::Update(float dt)
{
	/*if (isKeyPressed(EventKeyboard::KeyCode::KEY_F2))
	{
		utils::captureScreen(, "Screenshots/testcapture.png");
	}*/
}

void InputManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (Key_map.find(keyCode) == Key_map.end()) {
		Key_map[keyCode] = std::chrono::high_resolution_clock::now();
	}
	for (int i = 0; i < m_onKeyPress_EventMap.size(); ++i)
	{
		m_onKeyPress_EventMap[i](keyCode,event);
	}
}
void InputManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Key_map.erase(keyCode);

	for (int i = 0; i < m_onKeyRelease_EventListMap.size(); ++i)
	{
		m_onKeyRelease_EventListMap[i](keyCode,event);
	}
}
bool InputManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode code)
{
	//check if key has been pressed and inside key_map
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
}
void InputManager::onMouseUp(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	m_mousedown = false;
}
void InputManager::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	m_mousedown = true;
}
void InputManager::onMouseScroll(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}

bool InputManager::isMouseDown()
{
	return m_mousedown;
}

void InputManager::afterScreenCapture(bool somebool, const std::string& somestring)
{
	CCLOG(std::to_string(somebool).c_str());
	CCLOG(somestring.c_str());
	CCLOG("screencapded");
#ifdef __APPLE__
	sdkbox::FBShareInfo info;
	info.type = sdkbox::FB_PHOTO;
	info.title = "My Photo";
	info.image = somebool;
	sdkbox::PluginFacebook::dialog(info);
#endif
}