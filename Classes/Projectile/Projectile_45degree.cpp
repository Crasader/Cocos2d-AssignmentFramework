#include "Projectile_45degree.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
#include "SceneManager.h"
Projectile_45degree::Projectile_45degree()
{
}

Projectile_45degree::~Projectile_45degree()
{
}

void Projectile_45degree::Init()
{
	destroy = false;
	lifetime = 3.f;
	damage = 1;
	offset = Vec2::ZERO;
	node = Node::create();
	node->setPosition(PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition() + offset);
	sprite = Sprite::create("Projectile/projectile1.png");
	sprite->setName("BaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 10.f;
	angle = 35.f;
	Vec2 temp_dir = Vec2(0, 10);
	temp_dir = temp_dir.rotateByAngle(Vec2::ZERO, CC_DEGREES_TO_RADIANS(angle));
	Direction_Vector = temp_dir.getNormalized();//Vec2(cos(CC_DEGREES_TO_RADIANS(angle)), sin(CC_DEGREES_TO_RADIANS(angle)));
	Direction_Vector.normalize();
	SceneManager::getInstance().get_current_scene()->addChild(node);
}

void Projectile_45degree::Init_other_side()
{
	destroy = false;
	lifetime = 3.f;
	damage = 1;
	offset = Vec2::ZERO;
	node = Node::create();
	node->setPosition(PlayerManager::getInstance().get_Player(0)->get_Node()->getPosition() + offset);
	sprite = Sprite::create("Projectile/projectile1.png");
	sprite->setName("BaseProjectile");
	SceneManager::AdjustContentSize(sprite, 0.015f);
	node->addChild(sprite);
	movement_spd = 10.f;
	angle = -35.f;
	Vec2 temp_dir = Vec2(0, 10);
	temp_dir = temp_dir.rotateByAngle(Vec2(0,0), CC_DEGREES_TO_RADIANS(angle));
	Direction_Vector = temp_dir.getNormalized();
	SceneManager::getInstance().get_current_scene()->addChild(node);
	ProjectileManager::getInstance().AddProjectile(this);
}

BaseProjectile* Projectile_45degree::create()
{
	Projectile_45degree* first = new Projectile_45degree();
	Projectile_45degree* second = new Projectile_45degree();
	second->Init_other_side();
	return first;
}

BaseProjectile* Projectile_45degree::create_with_offset(Vec2 offset)
{
	Projectile_45degree* first = new Projectile_45degree();
	first->set_offset(offset);
	Projectile_45degree* second = new Projectile_45degree();
	second->set_offset(offset);
	second->Init_other_side();
	return first;
}