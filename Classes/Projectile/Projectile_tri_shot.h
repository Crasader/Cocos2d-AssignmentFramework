#ifndef PROJECTILE_TRI_SHOT_H_
#define PROJECTILE_TRI_SHOT_H_

#include "BaseProjectile.h"

class Projectile_tri_shot : BaseProjectile
{
public:
	Projectile_tri_shot();
	~Projectile_tri_shot();

	void Init();
	void Init_other_side();
	void Init_middle_side();
	static BaseProjectile* create();
	static BaseProjectile* create_with_offset(Vec2 offset);
protected:
	float angle;
};



#endif