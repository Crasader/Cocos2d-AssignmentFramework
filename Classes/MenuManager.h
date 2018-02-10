#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H


#include "cocos2d.h"

using namespace cocos2d;

class MenuManager
{

public:

	static MenuManager *getInstance()
	{
		if (instance == nullptr)
			instance = new MenuManager();
		
		return instance;
	}

	void Init();
	void Update(float dt);



	//Play Game
	//Instructions
	//Credits
	//Options
	//exits

private:
	MenuManager();
	~MenuManager();

	Menu *sceneMenuLayer;

	std::vector<MenuItemImage*> menu_ButtonsList;

	static MenuManager *instance;
};








#endif


