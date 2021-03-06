
#ifdef __APPLE__
#include "BaseProjectile.h"
#else
#include "Projectile\BaseProjectile.h"
#endif
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
BaseProjectile::BaseProjectile()
{
}

BaseProjectile::~BaseProjectile()
{
}

void BaseProjectile::Init()
{
	destroy = false;
	lifetime = 3.f;
	damage = 1;
	offset = Vec2::ZERO;
	node = Node::create();
	sprite = Sprite::create("Projectile/projectile1.png");
	sprite->setName("BaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 10.f;
	Direction_Vector = Vec2(0, 1);
	SceneManager::getInstance().get_current_scene()->addChild(node);


	Player* temp_player = PlayerManager::getInstance().get_Player(0);
	node->setPosition(Vec2(temp_player->get_Node()->getPosition()));//getPosition() + offset);
	
	
}

void BaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("BaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 10.f;
	Direction_Vector = Direction_vector;
	SceneManager::getInstance().get_current_scene()->addChild(node);
}

void BaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("BaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	SceneManager::getInstance().get_current_scene()->addChild(node);
}

void BaseProjectile::Update(float delta)
{
	lifetime -= delta;
	if (lifetime <= 0 && !destroy)
		destroy = true;

	Collision();

	auto moveEvent = MoveBy::create(0.0f, Direction_Vector * movement_spd);
	node->runAction(moveEvent);

}

Node* BaseProjectile::get_Node()
{
	return node;
}

void BaseProjectile::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

BaseProjectile* BaseProjectile::get_new_class_instance()
{
	return new BaseProjectile();
}

BaseProjectile* BaseProjectile::create()
{
	return new BaseProjectile();
}

BaseProjectile* BaseProjectile::create_with_offset(Vec2 offset)
{
	BaseProjectile* temp = new BaseProjectile();
	temp->set_offset( offset);
	return temp;
}

void BaseProjectile::Collision()
{
#define ENEMYLIST EnemyManager::getInstance().EnemyList
	CCRect projectile_rect = CCRectMake(
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

		if (projectile_rect.intersectsRect(enemy_rect))
		{
			ENEMYLIST.at(i)->get_hit(damage);
			destroy = true;
			break;
		}
	}
}

void BaseProjectile::set_offset(Vec2 offset)
{
	this->offset = offset;
}

void BaseProjectile::release()
{
	SceneManager::getInstance().get_current_scene()->removeChild(node);
}
