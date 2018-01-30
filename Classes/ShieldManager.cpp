#include "ShieldManager.h"
#include "MasterManager.h"
ShieldManager::ShieldManager()
{
	MASTERMANAGER_CALLBACK_INIT_FUNC(ShieldManager, Init)
	MASTERMANAGER_CALLBACK_UPDATE_FUNC(ShieldManager, Update)
}

ShieldManager::~ShieldManager()
{
}

void ShieldManager::Init()
{
	if (ShieldList.size() > 0)
		Release();
}

void ShieldManager::Update(float dt)
{
	for (vector<Shield*>::iterator it = ShieldList.begin(); it != ShieldList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			Shield* t = *it;
			it = ShieldList.erase(it);
			t->release();
			delete t;
		}
		else
		{
			it++;
		}
	}
}

void ShieldManager::CreateShield(string sprite_filename, Player* player)
{
	Shield* temp = new Shield();
	temp->Init(sprite_filename, player);
	ShieldList.push_back(temp);
}

void ShieldManager::Release()
{
	while (ShieldList.size() > 0)
	{
		Shield* shield = ShieldList.back();
		shield->release();
		ShieldList.pop_back();
		delete shield;
	}
}