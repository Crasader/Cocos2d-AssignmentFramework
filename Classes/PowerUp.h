#ifndef POWERUP_H_
#define POWERUP_H_

#include <vector>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class PowerUp
{

public:

	PowerUp();
	~PowerUp();

	enum TypesOfPowerUp
	{
		NOTHING = 0,
		HEAL,
		SHIELD,
		MULTISHOT,
	}typeOfPowerUp;

	void Init(string sprite_filename, TypesOfPowerUp types, Vec2 position);
	void Update(float delta);
	Node* get_Node();
	Node* get_spriteNode();
	virtual Sprite* getSprite(void) { return sprite; }
	void set_Position(float x, float y);
	static PowerUp* create(string name);
	static PowerUp* create(string sprite_filename, TypesOfPowerUp types, Vec2 position);
	void release();

	bool destroy;
private:
	void Set_Name(string name);

	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;
};



#endif