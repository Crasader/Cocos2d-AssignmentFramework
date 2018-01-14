#include "EnemyBaseProjectile.h"


EnemyBaseProjectile::EnemyBaseProjectile()
	: destroy(false),
	lifetime(3.f),
	damage(1)
{
}

EnemyBaseProjectile::~EnemyBaseProjectile()
{
}

void EnemyBaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("EnemyBaseProjectile");
	node->addChild(sprite);
	movement_spd = 10.f;
	Direction_Vector = Direction_vector;
	CCDirector::getInstance()->getRunningScene()->addChild(node);
	
	
}

void EnemyBaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("EnemyBaseProjectile");
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void EnemyBaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Player player, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("EnemyBaseProjectile");
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	CCDirector::getInstance()->getRunningScene()->addChild(node);

	player = Player::create();
}


void EnemyBaseProjectile::Update(float delta)
{
	lifetime -= delta;
	if (lifetime <= 0 && !destroy)
		destroy = true;

	Collision();

	auto moveEvent = MoveBy::create(0.0f, Direction_Vector * movement_spd);
	node->runAction(moveEvent);

}

Node* EnemyBaseProjectile::get_Node()
{
	return node;
}

void EnemyBaseProjectile::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

EnemyBaseProjectile* EnemyBaseProjectile::create()
{
	return new EnemyBaseProjectile();
}

void EnemyBaseProjectile::Collision()
{
//#define PLAYERHIT Player::getInstance().get_Node()

	CCRect projectile_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);

	
		CCRect enemy_rect = CCRectMake(
			player->get_Node()->getPosition().x - (player->getSprite()->getContentSize().width * 0.5f),
			player->get_Node()->getPosition().y - (player->getSprite()->getContentSize().height * 0.5f),
			player->get_Node()->getContentSize().width,
			player->get_Node()->getContentSize().height
		);

		if (projectile_rect.intersectsRect(enemy_rect))
		{
			player->get_hit(damage);
			destroy = true;
			//break;
		}
	
}

void EnemyBaseProjectile::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
}
