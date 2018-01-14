#include "Projectile_45degree.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
Projectile_45degree::Projectile_45degree()
{
}

Projectile_45degree::~Projectile_45degree()
{
}

void Projectile_45degree::Init()
{
	node = Node::create();
	node->setPosition(PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition());
	sprite = Sprite::create("Projectile/projectile1.png");
	sprite->setName("BaseProjectile");
	node->addChild(sprite);
	movement_spd = 10.f;
	angle = 45.f;
	Direction_Vector = Vec2(cos(angle), sin(angle));
	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void Projectile_45degree::Init_other_side()
{
	node = Node::create();
	node->setPosition(PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition());
	sprite = Sprite::create("Projectile/projectile1.png");
	sprite->setName("BaseProjectile");
	node->addChild(sprite);
	movement_spd = 10.f;
	angle = 135.f;
	Direction_Vector = Vec2(cos(angle), sin(angle));
	CCDirector::getInstance()->getRunningScene()->addChild(node);
	ProjectileManager::getInstance().AddProjectile(this);
}

BaseProjectile* Projectile_45degree::create()
{
	Projectile_45degree* first = new Projectile_45degree();
	Projectile_45degree* second = new Projectile_45degree();
	second->Init_other_side();
	return new Projectile_45degree();
}