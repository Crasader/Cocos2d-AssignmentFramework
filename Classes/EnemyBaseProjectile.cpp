#include "EnemyBaseProjectile.h"
#include "SceneManager.h"

EnemyBaseProjectile::EnemyBaseProjectile()
	: destroy(false),
	lifetime(30.f),
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
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 2.f;
	Direction_Vector = Direction_vector;
	SceneManager::getInstance().get_current_scene()->addChild(node);
	
	
}

void EnemyBaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("EnemyBaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	SceneManager::getInstance().get_current_scene()->addChild(node);
}

void EnemyBaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Player player, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("EnemyBaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	SceneManager::getInstance().get_current_scene()->addChild(node);

	//PlayerManager::getInstance().get_Player(0)->get_Node()
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
			PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition().x/* - (PlayerManager::getInstance().get_Player(0)->getSprite()->getContentSize().width * 0.5f)*/,
			PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition().y /*- (PlayerManager::getInstance().get_Player(0)->getSprite()->getContentSize().height * 0.5f)*/,
			/*PlayerManager::getInstance().get_Player(0)->get_Node()->getContentSize().width*/ 0.5f,
			/*PlayerManager::getInstance().get_Player(0)->get_Node()->getContentSize().height*/
			0.5f
		);

		if (projectile_rect.intersectsRect(enemy_rect))
		{
			PlayerManager::getInstance().get_Player(0)->get_hit(damage);
			destroy = true;
			//break;
		}
	
}

void EnemyBaseProjectile::release()
{
	SceneManager::getInstance().get_current_scene()->removeChild(node);
}

int EnemyBaseProjectile::get_damage()
{
	return damage;
}
