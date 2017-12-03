#ifndef PLAYER_H_
#define PLAYER_H_

#include "BaseProjectile.h"
#include <vector>
class Player
{
	
public:

	Player();
	~Player();

	enum Movement_Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	void Init(string sprite_filename);
	void Update(float delta);
	Node* get_Node();
	Node* get_spriteNode();
	void set_Position(float x, float y);
	void Move(Movement_Direction dir);
	void Shoot();

	static Player* create(string name);
	
private:
	void Set_Name(string name);
	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;
	float movement_spd;
	std::vector<BaseProjectile*> ProjectileList;
};



#endif