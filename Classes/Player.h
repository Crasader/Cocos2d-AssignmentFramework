#ifndef PLAYER_H_
#define PLAYER_H_

#include "ProjectileManager.h"
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

	enum Moving_State
	{
		Tilting_Left,
		Tilting_Right,
		Idle
	};

	void Init(string sprite_filename);
	void Update(float delta);
	Node* get_Node();
	Node* get_spriteNode();
	void set_Position(float x, float y);
	Animate* Add_animation(string plist_filename, string animation__name);
	void Move(Movement_Direction dir);
	void Shoot();
	void Set_moving_state(Moving_State mov_st);
	int get_hp();

	static Player* create(string name);
	
private:
	void Set_Name(string name);
	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;
	float movement_spd;
	Vector<SpriteFrame*> animFrames_tilt_left;
	Vector<SpriteFrame*> animFrames_tilt_right;
	Vector<SpriteFrame*> animFrames_idle;
	std::vector<BaseProjectile*> ProjectileList;
	Moving_State moving_state;
	Animate* idle_anim;
	SpriteFrame* original_sprite;

	int hp;
};



#endif