#include "Shield.h"
#include "EnemyManager.h"
#include "PowerUpManager.h"

Shield::Shield()
	: destroy(false),
	shieldValue(10)
{
}

Shield::~Shield()
{
}

void Shield::Init(string sprite_filename, Player* player)
{
	node = Node::create();
	node->setPosition(player->get_Node()->getPosition());
	sprite = Sprite::create("PowerUp/" + sprite_filename);
	sprite->setName("Shield");
	node->addChild(sprite);
	CCDirector::getInstance()->getRunningScene()->addChild(node);
	this->player = player;
}


void Shield::Update(float delta)
{
	Collision();
	node->setPosition(player->get_Node()->getPosition());

	if (shieldValue <= 0)
	{
		destroy = true;
	}
}

Node* Shield::get_Node()
{
	return node;
}

void Shield::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

Shield* Shield::create()
{
	return new Shield();
}

void Shield::get_hit(int damage)
{
	shieldValue -= damage;
}

void Shield::Collision()
{
#define ENEMYLIST EnemyManager::getInstance().EnemyList
#define POWERUPLIST PowerUpManager::getInstance().PowerUpList
#define ENEMYPROJECTILELIST	EnemyProjectileManager::getInstance().ProjectileList

	CCRect Shield_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);

	for (int i = 0; i < ENEMYLIST.size(); ++i)
	{
		CCRect enemy_rect = CCRectMake(
			ENEMYLIST.at(i)->get_Node()->getPosition().x - (ENEMYLIST.at(i)->getSprite()->getContentSize().width * 0.5f),
			ENEMYLIST.at(i)->get_Node()->getPosition().y - (ENEMYLIST.at(i)->getSprite()->getContentSize().height * 0.5f),
			ENEMYLIST.at(i)->getSprite()->getContentSize().width,
			ENEMYLIST.at(i)->getSprite()->getContentSize().height
		);

		if (Shield_rect.intersectsRect(enemy_rect))
		{
			get_hit(ENEMYLIST.at(i)->get_damage());
			ENEMYLIST.at(i)->destroy = true;
			break;
		}
	}


	for (int i = 0; i < POWERUPLIST.size(); ++i)
	{
		CCRect powerup_rect = CCRectMake(
			POWERUPLIST.at(i)->get_Node()->getPosition().x - (POWERUPLIST.at(i)->getSprite()->getContentSize().width * 0.5f),
			POWERUPLIST.at(i)->get_Node()->getPosition().y - (POWERUPLIST.at(i)->getSprite()->getContentSize().height * 0.5f),
			POWERUPLIST.at(i)->getSprite()->getContentSize().width,
			POWERUPLIST.at(i)->getSprite()->getContentSize().height
		);

		if (Shield_rect.intersectsRect(powerup_rect))
		{
			switch (POWERUPLIST.at(i)->typeOfPowerUp)
			{
			case PowerUp::SHIELD:
				shieldValue = 10;
				POWERUPLIST.at(i)->destroy = true;
				break;
			default:
				break;
			}

			break;
		}
	}

	for (int i = 0; i < ENEMYPROJECTILELIST.size(); ++i)
	{
		CCRect enemyProjectile_rect = CCRectMake(
			ENEMYPROJECTILELIST.at(i)->get_Node()->getPosition().x - (ENEMYPROJECTILELIST.at(i)->getSprite()->getContentSize().width * 0.5f),
			ENEMYPROJECTILELIST.at(i)->get_Node()->getPosition().y - (ENEMYPROJECTILELIST.at(i)->getSprite()->getContentSize().height * 0.5f),
			ENEMYPROJECTILELIST.at(i)->getSprite()->getContentSize().width,
			ENEMYPROJECTILELIST.at(i)->getSprite()->getContentSize().height
		);

		if (Shield_rect.intersectsRect(enemyProjectile_rect))
		{
			get_hit(ENEMYPROJECTILELIST.at(i)->get_damage());
			ENEMYPROJECTILELIST.at(i)->destroy = true;
			break;
		}
	}
}

void Shield::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
}
