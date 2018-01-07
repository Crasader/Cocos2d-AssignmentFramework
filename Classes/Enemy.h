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


	void Init(string sprite_filename);
	void Update(float dt);
	Node* get_Node();
	Node* get_spriteNode();
	void set_Position(float x, float y);
	Animate* Add_animation(string plist_filename, string animation__name);
	void Shoot();
	int get_hp();

	static Enemy* create(string name);


private:
	void Set_Name(string name);
	float movement_spd;

	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;

	int hp;

};





#endif // !ENEMY_H








