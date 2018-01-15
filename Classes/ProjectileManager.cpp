#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	CCLOG("ProjectileManager singleton created");
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::Add_Create_Functions()
{
	create_ptr_list.push_back(BaseProjectile::create);
	create_ptr_list.push_back(Projectile_45degree::create);
	create_ptr_list.push_back(Projectile_tri_shot::create);

}

void ProjectileManager::Init()
{
	//ProjectileCreatePtr temp_func_ptr = &BaseProjectile::create();
	//create_ptr_list.push_back(BaseProjectile::create());
	Add_Create_Functions();
	CCLOG("ProjectileManager Init");
}

void ProjectileManager::Update(float dt)
{
	for (vector<BaseProjectile*>::iterator it = ProjectileList.begin(); it != ProjectileList.end();)
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			BaseProjectile* t = *it;
			it = ProjectileList.erase(it);
			t->release();
			delete t;
		}
		else
		{
			it++;
		}
	}

	/*int to_destroy = 0;
	vector<BaseProjectile*> projectile_to_destroy;
	for (int i = 0; i < ProjectileList.size(); i++)
	{
		ProjectileList.at(i)->Update(dt);
		if (ProjectileList.at(i)->destroy)
		{
			projectile_to_destroy.push_back(ProjectileList.at(i));
		}
	}
	while (projectile_to_destroy.size() > 0)
	{
		//ProjectileList.(projectile_to_destroy.back());
		projectile_to_destroy.back()->release();

	}*/
	/*vector<BaseProjectile*>::iterator it = ProjectileList.begin();
	while (it != ProjectileList.end())
	{
		(*it)->Update(dt);
		if ((*it)->destroy)
		{
			it = ProjectileList.erase(it);
			if (it != ProjectileList.end())
				it++;
		}
			
		else
		{
			it++;
		}
	}*/

}

void ProjectileManager::CreateProjectile(int type)
{
	BaseProjectile* temp;
	switch (type)
	{
	case 0:
		temp = BaseProjectile::create();
		break;
	case 1:
		temp = Projectile_45degree::create();
		break;
	case 2:
		temp = Projectile_tri_shot::create();
		break;
	default:
		temp = BaseProjectile::create();
		break;
	}
	temp->Init();
	ProjectileList.push_back(temp);
}

void ProjectileManager::CreateProjectile(int type, Vec2 offset)
{
	BaseProjectile* temp;
	switch (type)
	{
	case 0:
		temp = BaseProjectile::create_with_offset(offset);
		break;
	case 1:
		temp = Projectile_45degree::create_with_offset(offset);
		break;
	case 2:
		temp = Projectile_tri_shot::create_with_offset(offset);
		break;
	default:
		break;
	}
	temp->Init();
	ProjectileList.push_back(temp);
}

void ProjectileManager::CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	BaseProjectile* temp = new BaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position);
	ProjectileList.push_back(temp);
}
void ProjectileManager::CreateProjectile(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	BaseProjectile* temp = new BaseProjectile();
	temp->Init(sprite_filename, Direction_vector, position,lifetime);
	ProjectileList.push_back(temp);
}

void ProjectileManager::AddProjectile(BaseProjectile* projectile)
{
	ProjectileList.push_back(projectile);
}

int ProjectileManager::get_Number_of_Projectiles()
{
	return ProjectileList.size();
}

void ProjectileManager::Release()
{
	while (ProjectileList.size() > 0)
	{
		BaseProjectile* projectile = ProjectileList.back();
		projectile->release();
		ProjectileList.pop_back();
		delete projectile;
	}
}