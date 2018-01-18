#include "PowerUpManager.h"
#include "MasterManager.h"
PowerUpManager::PowerUpManager()
{
	MASTERMANAGER_CALLBACK_INIT_FUNC(PowerUpManager, Init)
	MASTERMANAGER_CALLBACK_UPDATE_FUNC(PowerUpManager, Update)
}

PowerUpManager::~PowerUpManager()
{
}

void PowerUpManager::Init()
{

}

void PowerUpManager::Update(float dt)
{
	for (vector<PowerUp*>::iterator it = PowerUpList.begin(); it != PowerUpList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			PowerUp* t = *it;
			it = PowerUpList.erase(it);
			t->release();
			delete t;
		}
		else
		{
			it++;
		}
	}
}

void PowerUpManager::CreatePowerUp(string sprite_filename, PowerUp::TypesOfPowerUp types, Vec2 position)
{
	PowerUp* temp = PowerUp::create(sprite_filename, types, position);
	PowerUpList.push_back(temp);
}

void PowerUpManager::Release()
{

}