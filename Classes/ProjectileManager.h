#ifndef PROJECTILE_MANAGER_H_
#define PROJECTILE_MANAGER_H_

#include "BaseProjectile.h"

class ProjectileManger
{
public:
	ProjectileManger();
	~ProjectileManger();

	void Update(float dt);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	void CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);

private:
	std::vector<BaseProjectile*> ProjectileList;
};



#endif