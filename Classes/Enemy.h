#ifndef ENEMY_H
#define ENEMY_H

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Enemy
{
public:
	Enemy();
	~Enemy();


	virtual void Init(string sprite_filename);
	virtual void Init(string sprite_filename, Vec2 position);
	virtual void Update(float dt);
	virtual Node* get_Node();
	virtual Node* get_spriteNode();
	virtual Sprite* getSprite(void) { return sprite; }
	virtual void set_Position(float x, float y);
	virtual Animate* Add_animation(string plist_filename, string animation__name);
	virtual void Shoot();
	virtual int get_hp();
	virtual int get_damage();
	virtual void get_hit(int damage);

	static Enemy* create(string name);
	static Enemy* create(string name, string sprite_filename, Vec2 position);
	virtual void release();

	bool destroy;
private:
	void Set_Name(string name);
	float movement_spd;

	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;

	int hp;
	int damage;
};





#endif // !ENEMY_H








