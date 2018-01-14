#include "EnemyManager.h"
#include "WaveManager.h"
EnemyManager::EnemyManager()
{
	CCLOG("EnemyManager singleton created");
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	CCLOG("EnemyManager Init");
}
void EnemyManager::Update(float dt)
{
	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			Enemy* t = *it;
			it = EnemyList.erase(it);
			t->release();
			delete t;
			if (WaveManager::getInstance().Wave_List.size() != 0)
				++WaveManager::getInstance().get_current_wave()->currEnemiesKilled;
		}
		else
		{
			it++;
		}
	}
}
void EnemyManager::CreateEnemy(string name, string sprite_filename, Vec2 position)
{
	Enemy* temp = Enemy::create(name, sprite_filename, position);
	EnemyList.push_back(temp);
}
int EnemyManager::get_Number_of_Enemies()
{
	return EnemyList.size();
}

void EnemyManager::Release()
{
	while (EnemyList.size() > 0)
	{
		Enemy* enemy = EnemyList.back();
		enemy->release();
		EnemyList.pop_back();
		delete enemy;
	}
}