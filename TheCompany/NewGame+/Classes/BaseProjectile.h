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
	
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	virtual void Update(float delta);
	virtual Node* get_Node();
	virtual void set_Position(float x, float y);
	static BaseProjectile* create();

	void retain();
	void release();

	bool destroy;
private:
	float movement_spd;
	Sprite* sprite;
	Node* node;
	Vec2 Direction_Vector;
	float lifetime;
};



#endif
