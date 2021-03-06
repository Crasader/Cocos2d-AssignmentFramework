

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
	//MenuItemImage* playButton = MenuItemImage::create("LightBlue_Front1.png", "Blue_Front1.png");
	//set origin to middle
	//playButton->setAnchorPoint(Vec2(0.5f, 0.5f));

	float x = SceneManager::getInstance().currScene_playingSize.width * 0.5f;
	float y = SceneManager::getInstance().currScene_playingSize.height;
	//playButton->setPosition(Vec2(x,y)); //set to middle of screen
	//add it to scene menu layer
	//sceneMenuLayer->addChild(playButton);

	//playButton->setCallback(CC_CALLBACK_0(MenuManager::ExampleFunction,this));

	if (SceneManager::getInstance().currSceneName == "MenuScene")
	{
		createButtonImageInScene("menu_img/playbtn.png", "menu_img/playbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y * 0.35f))->setCallback(CC_CALLBACK_0(MenuManager::PlayBtnStart, this));

		createButtonImageInScene("menu_img/controlsbtn.png", "menu_img/controlsbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y* 0.28f))->setCallback(CC_CALLBACK_0(MenuManager::ControlBtn_Pressed, this));;
		createButtonImageInScene("menu_img/creditsbtn.png", "menu_img/creditsbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y* 0.21f))->setCallback(CC_CALLBACK_0(MenuManager::CreditsBtn_Pressed, this));;
		createButtonImageInScene("menu_img/optionbtn_selected.png", "menu_img/optionbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y* 0.14f))->setCallback(CC_CALLBACK_0(MenuManager::OptionsBtn_Pressed, this));;

		createButtonImageInScene("menu_img/exitbtn.png", "menu_img/exitbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y* 0.07f))->setCallback(CC_CALLBACK_0(MenuManager::ExitBtn_Pressed, this));;

	}
	else if (SceneManager::getInstance().currSceneName == "CreditScene" ||
		SceneManager::getInstance().currSceneName == "InstructionScene")
	{
		createButtonImageInScene("menu_img/backbtn.png", "menu_img/backbtn_selected.png",
			Vec2(0.5f, 0.5f), Vec2(x, y* 0.07f))->setCallback(CC_CALLBACK_0(MenuManager::ReturnMainMenu, this));

	}
	else
	{
		return;
	}
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

void MenuManager::PlayBtnStart()
{
	//Enter gameplay
	CCLOG("Start game");
	SceneManager::getInstance().Change_Scene("HelloWorld");
}

void MenuManager::ControlBtn_Pressed()
{
	CCLOG("View intructions");
	SceneManager::getInstance().Change_Scene("InstructionScene");
}

void MenuManager::CreditsBtn_Pressed()
{
	CCLOG("Enter Credit page");
	SceneManager::getInstance().Change_Scene("CreditScene");
}

void MenuManager::OptionsBtn_Pressed()
{
	CCLOG("Options not done");
}

void MenuManager::ExitBtn_Pressed()
{
	Director::getInstance()->end();
	CCLOG("Quit game");
}

void MenuManager::ReturnMainMenu()
{
	SceneManager::getInstance().Change_Scene("MenuScene");
}


