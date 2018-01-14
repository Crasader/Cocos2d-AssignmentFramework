#ifndef SHIELD_H_
#define SHIELD_H_

#include "cocos2d.h"
#include "Player.h"
using namespace std;
using namespace cocos2d;
class Shield
{
public:
	Shield();
	~Shield();

	virtual void Init(string sprite_filename, Player* player);

	virtual void Update(float delta);
	virtual Node* get_Node();
	virtual void set_Position(float x, float y);
	static Shield* create();
	virtual void Collision();
	void get_hit(int damage);
	virtual void release();
	bool destroy;
protected:
	Sprite* sprite;
	Node* node;
	Player* player;

	int shieldValue;
};



#endif