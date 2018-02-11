

#include "MenuManager.h"
#include "MasterManager.h"
#include "SceneManager.h"

MenuManager *MenuManager::instance;
Menu *MenuManager::sceneMenuLayer;
#define CURRENTSCENE SceneManager::getInstance().get_current_scene()

MenuManager::MenuManager()
{

	MasterManager::getInstance().Add_Init_Function([]() 
	{
		MenuManager::getInstance()->Init();
	});

	MasterManager::getInstance().Add_Update_Function([](float dt)
	{
		MenuManager::getInstance()->Update(dt);
	});
}

MenuManager::~MenuManager()
{

}

void MenuManager::Init()
{	
	// point to scene menu layer
	sceneMenuLayer = CURRENTSCENE->m_MenuLayer;
	//set origin to middle
	CURRENTSCENE->m_MenuLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	//create a button with image
	MenuItemImage* playButton = MenuItemImage::create("LightBlue_Front1.png", "Blue_Front1.png");
	//set origin to middle
	playButton->setAnchorPoint(Vec2(0.5f, 0.5f));

	float x = SceneManager::getInstance().currScene_playingSize.width * 0.5f;
	float y = SceneManager::getInstance().currScene_playingSize.height * 0.5f;
	playButton->setPosition(Vec2(x,y)); //set to middle of screen
	//add it to scene menu layer
	sceneMenuLayer->addChild(playButton);

	playButton->setCallback(CC_CALLBACK_0(MenuManager::ExampleFunction,this));
}

void MenuManager::Update(float dt)
{

}

void MenuManager::ExampleFunction()
{
	//do whatever
	CCLOG("test button success");
}


MenuItemImage* MenuManager::createButtonImage(const std::string& normalImage, const std::string& selectedImage, Vec2 anchor, Vec2 position)
{
	MenuItemImage* temp = MenuItemImage::create(normalImage, selectedImage);
	//set origin to middle
	temp->setAnchorPoint(anchor);
	temp->setPosition(position); //set to middle of screen
	return temp;
}

MenuItemImage* MenuManager::createButtonImageInScene(const std::string& normalImage, const std::string& selectedImage, Vec2 anchor, Vec2 position)
{
	MenuItemImage* temp = createButtonImage(normalImage, selectedImage, anchor, position);
	sceneMenuLayer->addChild(temp);
	return temp;
}