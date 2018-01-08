#include "PowerUp.h"

PowerUp::PowerUp() :
	destroy(false)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Init(string sprite_filename, TypesOfPowerUp types, Player* player, Vec2 position)
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
	this->player = player;

	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void PowerUp::Update(float delta)
{
	auto moveEvent = MoveBy::create(0.0f, Vec2(0, -1)); //* 1);
	node->runAction(moveEvent);

	Collision();

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

PowerUp* PowerUp::create(string sprite_filename, TypesOfPowerUp types, Player* player, Vec2 position)
{
	PowerUp* temp = new PowerUp();
	temp->Set_Name("Powerup");
	temp->Init(sprite_filename, types, player, position);
	return temp;
}

void PowerUp::Collision()
{
	CCRect Powerup_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);

	CCRect Player_rect = CCRectMake(
		player->get_Node()->getPosition().x - (player->getSprite()->getContentSize().width * 0.5f),
		player->get_Node()->getPosition().y - (player->getSprite()->getContentSize().height * 0.5f),
		player->getSprite()->getContentSize().width,
		player->getSprite()->getContentSize().height
	);

	if (Powerup_rect.intersectsRect(Player_rect))
	{
		destroy = true;
		switch (typeOfPowerUp)
		{
		case PowerUp::NOTHING:
			break;
		case PowerUp::HEAL:
			player->set_hp(player->get_hp() + 5);
			break;
		case PowerUp::SHIELD:
			break;
		case PowerUp::MULTISHOT:
			break;
		default:
			break;
		}

		
	}
}

void PowerUp::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
}

void PowerUp::Set_Name(string name)
{
	this->Name = name;
}
