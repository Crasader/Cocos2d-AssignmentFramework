#include "PowerUp.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#include "ShieldManager.h"
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

	SceneManager::getInstance().get_current_scene()->addChild(node);
}

void PowerUp::Update(float delta)
{
	auto moveEvent = MoveBy::create(0.0f, Vec2(0, -1)); //* 1);
	node->runAction(moveEvent);

	Collision();
}

void PowerUp::Collision()
{
	CCRect powerup_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);
	Player* player = PlayerManager::getInstance().get_Player(0);
	CCRect Player_rect = CCRectMake(
		player->get_Node()->getPosition().x - (player->getSprite()->getContentSize().width * 0.5f),
		player->get_Node()->getPosition().y - (player->getSprite()->getContentSize().height * 0.5f),
		player->getSprite()->getContentSize().width,
		player->getSprite()->getContentSize().height
	);


	if (Player_rect.intersectsRect(powerup_rect))
	{
		switch (typeOfPowerUp)
		{
		case PowerUp::HEAL:
			player->set_hp(player->get_hp() + 5);
			break;
		case PowerUp::SHIELD:
			ShieldManager::getInstance().CreateShield("shield_activated.png", player);
			break;
		case PowerUp::MULTISHOT:
			//bulletMultiply++;
			if (player->PowerLevel < player->m_Max_Power)
				++player->PowerLevel;
			break;

		default:
			break;
		}
		destroy = true;
	}
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
	SceneManager::getInstance().get_current_scene()->removeChild(node);
}

void PowerUp::Set_Name(string name)
{
	this->Name = name;
}
