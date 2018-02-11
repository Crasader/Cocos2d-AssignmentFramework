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
	m_mousedown = false;
	m_touching = false;

	m_onKeyPress_EventMap.clear();
	m_onKeyRelease_EventListMap.clear();

	m_onTouchBegin_EventListMap.clear();
	m_onTouchEnd_EventListMap.clear();
	m_onTouchMove_EventListMap.clear();
	Key_map.clear();

	auto k_listener = EventListenerKeyboard::create();
	k_listener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	k_listener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(k_listener, SceneManager::getInstance().get_current_scene());

	auto m_listener = EventListenerMouse::create();
	m_listener->onMouseDown = std::bind(&InputManager::onMouseDown, this, std::placeholders::_1);

	SceneManager::getInstance().get_current_scene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, SceneManager::getInstance().get_current_scene());

	auto t_listener = EventListenerTouchOneByOne::create();
	t_listener->onTouchBegan = CC_CALLBACK_2(InputManager::onTouchBegin, this);
	t_listener->onTouchEnded = CC_CALLBACK_2(InputManager::onTouchEnd, this);
	t_listener->onTouchMoved = CC_CALLBACK_2(InputManager::onTouchMove, this);
	
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

bool InputManager::onTouchBegin(Touch* touch, Event* event)
{
	m_touching = true;
	for (int i = 0; i < m_onTouchBegin_EventListMap.size(); ++i)
	{
		m_onTouchBegin_EventListMap[i](touch, event);
	}
	return true;
}

bool InputManager::onTouchEnd(Touch* touch, Event* event)
{
	m_touching = false;
	for (int i = 0; i < m_onTouchEnd_EventListMap.size(); ++i)
	{
		m_onTouchEnd_EventListMap[i](touch, event);
	}
	return true;
}

void InputManager::onTouchMove(Touch* touch, Event* event)
{
	for (int i = 0; i < m_onTouchMove_EventListMap.size(); ++i)
	{
		m_onTouchMove_EventListMap[i](touch, event);
	}
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