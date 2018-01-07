#include "ProjectileManager.h"

ProjectileManger::ProjectileManger()
{
}

ProjectileManger::~ProjectileManger()
{
}

void ProjectileManger::Update(float dt)
{

}

void ProjectileManger::CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	BaseProjectile* temp = new BaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position);
	ProjectileList.push_back(temp);
}
void ProjectileManger::CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	BaseProjectile* temp = new BaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position,lifetime);
	ProjectileList.push_back(temp);
}

