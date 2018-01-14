#ifndef WAVE_H_
#define WAVE_H_

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Wave
{
public:
	struct EnemyInfo
	{
		Vec2 Position;
		int Type;
	};

	Wave();
	~Wave();

	void Init();
	void Run();
	void Update(float dt);

	void RunWave(float dt);
	

	vector<EnemyInfo> List_of_enemy_info;

	static Wave* Create(int Enemy_Amount);
	static Wave* Create(int Enemy_Amount, Vec2 position);

	bool finished;
private:
	//int EnemyType;
	int Enemy_Amount;
	float tempDelay;
	float currEnemiesSpawned;
	int MaxEnemiesPerWave;
	float timeBtwnSpawn;

};



#endif