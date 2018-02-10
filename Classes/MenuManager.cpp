

#include "MenuManager.h"
#include "MasterManager.h"
#include "SceneManager.h"

MenuManager *MenuManager::instance;
#define CURRENTSCENE SceneManager::getInstance().get_current_scene()

MenuManager::MenuManager()
{

	MasterManager::getInstance().Add_Init_Function([]() 
	{
		MenuManager::getInstance()->Init();
	});

	
}

MenuManager::~MenuManager()
{

}

void MenuManager::Init()
{


	
	sceneMenuLayer = CURRENTSCENE->m_MenuLayer;

	MenuItemImage* playButton = MenuItemImage::create("LightBlue_Front1.png", "Blue_Front1.png");
	sceneMenuLayer->addChild(playButton);

	/*playButton->setPosition(Vec2(CURRENTSCENE->get_playingSize().width * 0.5f,
		CURRENTSCENE->get_playingSize().height * 0.5f));*/
	playButton->setPosition(Vec2(300.0f,300.0f));

}

void MenuManager::Update(float dt)
{

}



