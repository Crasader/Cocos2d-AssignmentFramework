#include "PowerUp.h"

PowerUp::PowerUp() :
	destroy(false)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(string sprite_filename, TypesOfPowerUp types, Vec2 position)
{
	node = Node::create();
	node->setName(Name);
	node->setPosition(position);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create("PowerUp/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	typeOfPowerUp = types;

	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void PowerUp::Update(float delta)
{
	auto moveEvent = MoveBy::create(0.0f, Vec2(0, -1)); //* 1);
	node->runAction(moveEvent);
}

Node* PowerUp::get_Node()
{
	return node;
}

Node* PowerUp::get_spriteNode()
{
	return spriteNode;
}

void PowerUp::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

PowerUp* PowerUp::create(string name)
{
	PowerUp* temp = new PowerUp();
	temp->Set_Name(name);
	return temp;
}

PowerUp* PowerUp::create(string sprite_filename, TypesOfPowerUp types, Vec2 position)
{
	PowerUp* temp = new PowerUp();
	temp->Set_Name("Powerup");
	temp->Init(sprite_filename, types, position);
	return temp;
}

void PowerUp::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
}

void PowerUp::Set_Name(string name)
{
	this->Name = name;
}
