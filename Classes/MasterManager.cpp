#include "MasterManager.h"
//include all managers
#include "SceneManager.h"
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "EnemyProjectileManager.h"
#include "PlayerManager.h"
#include "PowerUpManager.h"
#include "ProjectileManager.h"
#include "ShieldManager.h"
#include "WaveManager.h"
#include "MenuManager.h"
#include "InputManager\InputManager.h"
//vector<updatefunctionpointer> MasterManager::Update_list;
//vector<Initfunctionpointer> MasterManager::Init_list;


MasterManager::MasterManager() : SingletonsCreated(false)
{
	//Init();
	CCLOG("Master manager constructor");

	
}

MasterManager::~MasterManager()
{
}

void MasterManager::Init()
{
	if (!SingletonsCreated)
	{
		//Create all singletons
		SceneManager::getInstance();
		//AnimationManager::getInstance();
		CollisionManager::getInstance();
		EnemyManager::getInstance();
		EnemyProjectileManager::getInstance();
		PlayerManager::getInstance();
		PowerUpManager::getInstance();
		ProjectileManager::getInstance();
		ShieldManager::getInstance();
		WaveManager::getInstance();
		InputManager::getInstance();
		MenuManager::getInstance();

		SingletonsCreated = true;
	}

	/*SceneManager::getInstance().get_current_scene()->Add_Init_Function([]() {
		vector<Initfunctionpointer>::iterator it = MasterManager::getInstance().Init_list.begin();
		for (; it != MasterManager::getInstance().Init_list.end(); ++it)
		{
			(*it)();
		}
	});	
	*/

	vector<Initfunctionpointer>::iterator it = MasterManager::getInstance().Init_list.begin();
	for (; it != MasterManager::getInstance().Init_list.end(); ++it)
	{
		(*it)();
	}

	SceneManager::getInstance().get_current_scene()->Add_Update_Function([](float dt) {
		vector<updatefunctionpointer>::iterator it = MasterManager::getInstance().Update_list.begin();
		for (; it != MasterManager::getInstance().Update_list.end(); ++it)
		{
			(*it)(dt);
		}
	});

	CCLOG("MasterManager Init");
}

void MasterManager::update(float dt)
{
	vector<updatefunctionpointer>::iterator it = Update_list.begin();
	for (; it != Update_list.end(); ++it)
	{
		(*it)(dt);
	}
}
//template <class T>
void MasterManager::Add_Init_Function(Initfunctionpointer t)
{
	/*Init_list.push_back([target]()
	{
		target::Init();
	});*/

	Init_list.push_back(t);
	CCLOG("Init function received");
}
//template <class T>
void MasterManager::Add_Update_Function(updatefunctionpointer t)
{
	//updatefunctionpointer temp = fp;
	/*Update_list.push_back([target](float dt) 
	{
		target::Update(dt);
	});*/
	Update_list.push_back(t);
	CCLOG("Update function received");
}