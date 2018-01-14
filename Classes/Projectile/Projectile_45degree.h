#ifndef PROJECTILE_45DEGREE_H_
#define PROJECTILE_45DEGREE_H_
#include "Projectile\BaseProjectile.h"

class Projectile_45degree : BaseProjectile
{
public:
	Projectile_45degree();
	~Projectile_45degree();

	void Init();
	void Init_other_side();
	static BaseProjectile* create();
	static BaseProjectile* create_with_offset(Vec2 offset);
protected:
	float angle;
};




#endif