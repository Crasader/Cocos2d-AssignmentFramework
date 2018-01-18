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
}

void ShieldManager::Update(float dt)
{
	for (vector<Shield*>::iterator it = ProjectileList.begin(); it != ProjectileList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			Shield* t = *it;
			it = ProjectileList.erase(it);
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
	ProjectileList.push_back(temp);
}

void ShieldManager::Release()
{
	while (ProjectileList.size() > 0)
	{
		Shield* projectile = ProjectileList.back();
		projectile->release();
		ProjectileList.pop_back();
		delete projectile;
	}
}