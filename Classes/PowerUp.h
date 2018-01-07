#ifndef POWERUP_H_
#define POWERUP_H_

#include <vector>
#include "Player.h"
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

	void Init(string sprite_filename, TypesOfPowerUp types);
	void Update(float delta);
	Node* get_Node();
	Node* get_spriteNode();
	void set_Position(float x, float y);
	static PowerUp* create(string name);

private:
	void Set_Name(string name);

	Node* node;
	string Name;
	Sprite* sprite;
	Node* spriteNode;

	Player* player;

	virtual Sprite* getSprite(void) { return sprite; }
};



#endif