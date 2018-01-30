#include "Wave.h"
#include "EnemyManager.h"
#include "SceneManager.h"
#include <time.h>


Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::Init()
{
	tempDelay = 0;
	currEnemiesSpawned = 0;
	MaxEnemiesPerWave = 100;
	timeBtwnSpawn = 3.f;
	finished = false;
	currEnemiesKilled = 0;
}

void Wave::Run()
{
	while (List_of_enemy_info.size() > 0)
	{
		EnemyInfo temp_enemyinfo = List_of_enemy_info.back();
		if (temp_enemyinfo.Type == 1)
		{
			EnemyManager::getInstance().CreateEnemy("enemy1", "Enemy_Idle.png", temp_enemyinfo.Position);

		}
		List_of_enemy_info.pop_back();
	}
}

void Wave::Update(float dt)
{
	RunWave(dt);
	if (currEnemiesKilled >= MaxEnemiesPerWave)
	{
		finished = true;
	}
}

Wave* Wave::Create(int Enemy_Amount)
{
	Wave* temp = new Wave();	
	for (int i = 0; i < Enemy_Amount; ++i)
	{
		EnemyInfo temp_enemyinfo;
		temp_enemyinfo.Type = 1;
		float random = (float)cocos2d::RandomHelper::random_int(0, 896);
		temp_enemyinfo.Position = Vec2(random, 896);
		temp->List_of_enemy_info.push_back(temp_enemyinfo);
	}
	return temp;
}

Wave* Wave::Create(int Enemy_Amount, Vec2 position)
{
	Wave* temp = new Wave();
	for (int i = 0; i < Enemy_Amount; ++i)
	{
		EnemyInfo temp_enemyinfo;
		temp_enemyinfo.Type = 1;
		//float random = (float)cocos2d::RandomHelper::random_int(0, 896);
		temp_enemyinfo.Position = position;//Vec2(random, 896);
		temp->List_of_enemy_info.push_back(temp_enemyinfo);
	}
	return temp;
}


void Wave::RunWave(float dt)
{
	
	if (currEnemiesSpawned < MaxEnemiesPerWave)
	{
		tempDelay += dt;
		if (tempDelay >= timeBtwnSpawn)
		{
			int num_to_spawn = RandomHelper::random_int(1, 6);
			for (int i = 0; i < num_to_spawn; ++i)
			{
				float random = (float)cocos2d::RandomHelper::random_int(0, (int)(SceneManager::getInstance().currScene_playingSize.width));
				EnemyManager::getInstance().CreateEnemy("Enemy1", "Enemy_Idle.png", Vec2(random, SceneManager::getInstance().currScene_playingSize.height));
				Create(1, Vec2(random, (SceneManager::getInstance().currScene_playingSize.height)));
				++currEnemiesSpawned;
			}
			tempDelay = 0;
		}
		 
		
	}
	else
	{
		finished = true;
	}

}

void Wave::Release()
{
	if (List_of_enemy_info.size() > 0)
		List_of_enemy_info.clear();
}
