#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(string sprite_filename, TypesOfPowerUp types)
{
	node = Node::create();
	node->setName(Name);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create(sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	typeOfPowerUp = types;
}

void PowerUp::Update(float delta)
{
	auto moveEvent = MoveBy::create(0.f, Vec2(0, -1) * 1);
	spriteNode->runAction(moveEvent);

	/*if (sprite->getBoundingBox().intersectsRect(player->getSprite()->getBoundingBox()))
	{
		switch (typeOfPowerUp)
		{
		case PowerUp::NOTHING:
			break;
		case PowerUp::HEAL:
			break;
		case PowerUp::SHIELD:
			break;
		case PowerUp::MULTISHOT:
			break;
		default:
			break;
		}
	}*/
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

void PowerUp::Set_Name(string name)
{
	this->Name = name;
}
