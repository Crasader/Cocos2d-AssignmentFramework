#ifndef PROJECTILE_45DEGREE_H_
#define PROJECTILE_45DEGREE_H_
#include "Projectile\BaseProjectile.h"

class Projectile_45degree : BaseProjectile
{
public:
	Projectile_45degree();
	~Projectile_45degree();

	virtual void Init();
	void Init_other_side();
	static BaseProjectile* create();
private:
	float angle;
};




#endif