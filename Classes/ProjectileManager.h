#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_

#include "BaseProjectile.h"

class ProjectileManager
{
public:
	static ProjectileManager& getInstance()
	{
		static ProjectileManager Instance;
		return Instance;
	}

	void Init();
	void Update(float dt);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	void AddProjectile(BaseProjectile* projectile);
	std::vector<BaseProjectile*> ProjectileList;

	int get_Number_of_Projectiles();

	void Release();

	ProjectileManager(const ProjectileManager&) = delete;
	ProjectileManager& operator=(const ProjectileManager&) = delete;
private:
	ProjectileManager();
	~ProjectileManager();

	

	//static ProjectileManager* instance;
};



#endif