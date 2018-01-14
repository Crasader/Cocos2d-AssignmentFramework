#ifndef ENEMY_BASE_PROJECTILE_H_
#define ENEMY_BASE_PROJECTILE_H_

#include "cocos2d.h"
#include "Player.h"

using namespace std;
using namespace cocos2d;
class EnemyBaseProjectile
{
public:
	EnemyBaseProjectile();
	~EnemyBaseProjectile();

	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position);
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime);
	virtual void Init(string sprite_filename, Vec2 Direction_vector, Player player, Vec2 position, float lifetime);
	virtual void Update(float delta);
	virtual Node* get_Node();
	virtual void set_Position(float x, float y);
	static EnemyBaseProjectile* create();
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

	//Player* player;
};



#endif
