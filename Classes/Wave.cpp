#include "Wave.h"
#include "EnemyManager.h"
#include "SceneManager.h"

Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::Init()
{
	float tempDelay = 0;
	float currEnemiesSpawned = 0;
	int MaxEnemiesPerWave = 0;
	float timeBtwnSpawn = 0;
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


void Wave::RunWave()
{
	
	if (currEnemiesSpawned < MaxEnemiesPerWave)
	{
		//tempDelay += deltaTime;
		if (tempDelay >= timeBtwnSpawn)
		{
			float random = (float)cocos2d::RandomHelper::random_int(0.0f, (SceneManager::getInstance().currScene_playingSize.width));
			//EnemyManager::getInstance().CreateEnemy("Enemy1", "Enemy_Idle.png", Vec2(random, playingSize.height));
			Create(2, Vec2(random, (SceneManager::getInstance().currScene_playingSize.height)));


			tempDelay = 0;
		}

		currEnemiesSpawned++;
	}

}