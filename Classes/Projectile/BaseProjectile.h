#ifndef BASE_PROJECTILE_H_
#define BASE_PROJECTILE_H_

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class BaseProjectile
{
public:
	BaseProjectile();
	~BaseProjectile();
	
	virtual void Init();
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	virtual void Update(float delta);
	virtual Node* get_Node();
	virtual void set_Position(float x, float y);
	virtual BaseProjectile* get_new_class_instance();
	static BaseProjectile* create();
	virtual void Collision();

	virtual void release();
public:
	bool destroy;
protected:
	float movement_spd;
	Sprite* sprite;
	Node* node;
	Vec2 Direction_Vector;
	float lifetime;
	int damage;
	Vec2 offset;
};



#endif
