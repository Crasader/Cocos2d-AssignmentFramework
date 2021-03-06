#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_
#include "Enemy.h"
#include "GenericManager.h"
class EnemyManager : GenericManager
{
public:
	SINGLETON_CLASS(EnemyManager)

	void Init();
	void Update(float dt);
	void CreateEnemy(string name, string sprite_filename, Vec2 position);
	int get_Number_of_Enemies();

	void Release();
public:
	std::vector<Enemy*> EnemyList;
private:
	EnemyManager();
	~EnemyManager();
};



#endif