#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_

#include "Projectile\BaseProjectile.h"
#include "Projectile\Projectile_45degree.h"
#include "Projectile\Projectile_tri_shot.h"
//typedef BaseProjectile* (*ProjectileCreatePtr)();

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
	void CreateProjectile(int type);
	void CreateProjectile(int type,Vec2 offset);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	void AddProjectile(BaseProjectile* projectile);
	std::vector<BaseProjectile*> ProjectileList;

	int get_Number_of_Projectiles();

	void Release();

	ProjectileManager(const ProjectileManager&) = delete;
	ProjectileManager& operator=(const ProjectileManager&) = delete;
public:	
	//vector<function<BaseProjectile*()>> create_ptr_list;
private:
	ProjectileManager();
	~ProjectileManager();

	

	//static ProjectileManager* instance;
};



#endif