#include "Enemy.h"
#include "PowerUpManager.h"
#include "PlayerManager.h"

#define SHOOTING_SPEED 2.f

Enemy::Enemy() 
	: destroy(false),
	hp(2),
	damage(5)
{

}

Enemy::~Enemy()
{

}


void Enemy::Init(string sprite_filename)
{
	node = Node::create();
	node->setName(Name);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create("Enemy/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	movement_spd = 10.0f;
	shoot_timer = 0.f;


	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void Enemy::Init(string sprite_filename, Vec2 position)
{
	node = Node::create();
	node->setPosition(position);
	node->setName(Name);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create("Enemy/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	movement_spd = 10.0f;
	shoot_timer = 0.f;
	CCDirector::getInstance()->getRunningScene()->addChild(node);
}


void Enemy::Update(float dt)
{
	Collision();

	if (hp <= 0)
	{
		Death();
	}
	auto moveEvent = MoveBy::create(0.f, Vec2(0, -1) * 1);
	node->runAction(moveEvent);

	shoot_timer += dt;
	//CCLOG(std::to_string(shoot_timer).c_str());
	if (shoot_timer >= SHOOTING_SPEED)
	{
		Shoot();
		shoot_timer = 0;
	}
	
}

void Enemy::Set_Name(string name)
{
	this->Name = name;
}

void Enemy::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

void Enemy::Shoot()
{
	EnemyProjectileManager::getInstance().CreateEnemyProjectile("enemy_projectile1.png", Vec2(0.f, -4.f), node->getPosition());
}

int Enemy::get_hp()
{
	return hp;
}

int Enemy::get_damage()
{
	return damage;
}

void Enemy::get_hit(int damage)
{
	hp -= damage;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Enemy::Collision()
{
	CCRect Enemy_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);
#define PLAYER PlayerManager::getInstance().get_Player(0)
#define PLAYER_NODE PLAYER->get_Node()
	CCRect Player_rect = CCRectMake(
		PLAYER_NODE->getPosition().x - (PLAYER->getSprite()->getContentSize().width * 0.5f),
		PLAYER_NODE->getPosition().y - (PLAYER->getSprite()->getContentSize().height * 0.5f),
		PLAYER->getSprite()->getContentSize().width,
		PLAYER->getSprite()->getContentSize().height
	);

	if (Enemy_rect.intersectsRect(Player_rect))
	{
		PLAYER->get_hit(damage);
		destroy = true;
		hp = 0;
	}
}

void Enemy::Death()
{
	int random = (int)cocos2d::RandomHelper::random_int(0, 3);
	int random2 = (int)cocos2d::RandomHelper::random_int(0, 100);
	if (random2 < 30.f)
	{
		switch (random)
		{
		case 0:
			PowerUpManager::getInstance().CreatePowerUp("hp.png", PowerUp::TypesOfPowerUp::HEAL, node->getPosition());
			break;
		case 1:
			PowerUpManager::getInstance().CreatePowerUp("shield.png", PowerUp::TypesOfPowerUp::SHIELD, node->getPosition());
			break;
		case 2:
			PowerUpManager::getInstance().CreatePowerUp("multishot.png", PowerUp::TypesOfPowerUp::MULTISHOT, node->getPosition());
			break;
		default:
			break;
		}
	}


	destroy = true;
}

Enemy* Enemy::create(string name)
{
	Enemy* temp = new Enemy();
	temp->Set_Name(name);
	return temp;
}

Enemy* Enemy::create(string name, string sprite_filename, Vec2 position)
{
	Enemy* temp = new Enemy();
	temp->Set_Name(name);
	temp->Init(sprite_filename, position);
	return temp;
}

Node* Enemy::get_Node()
{
	return node;
}

Node* Enemy::get_spriteNode()
{
	return spriteNode;
}

Animate* Enemy::Add_animation(string plist_filename, string animation__name)
{
	auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile("Enemy/" + plist_filename);
	auto animation = cache->animationByName(animation__name);
	return Animate::create(animation);
}

void Enemy::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
}




