#ifndef ENEMY_PROJECTILE_MANAGER_H_
#define ENEMY_PROJECTILE_MANAGER_H_

#include "EnemyBaseProjectile.h"

class EnemyProjectileManager
{
public:
	static EnemyProjectileManager& getInstance()
	{
		static EnemyProjectileManager Instance;
		return Instance;
	}

	void Init();
	void Update(float dt);
	void CreateEnemyProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	void CreateEnemyProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	void AddEnemyProjectile(EnemyBaseProjectile* projectile);
	std::vector<EnemyBaseProjectile*> ProjectileList;

	int get_Number_of_Projectiles();

	void Release();

	EnemyProjectileManager(const EnemyProjectileManager&) = delete;
	EnemyProjectileManager& operator=(const EnemyProjectileManager&) = delete;
private:
	EnemyProjectileManager();
	~EnemyProjectileManager();



};



#endif