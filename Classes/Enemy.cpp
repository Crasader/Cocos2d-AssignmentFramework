#include "Enemy.h"

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



	CCDirector::getInstance()->getRunningScene()->addChild(node);
}


void Enemy::Update(float dt)
{
	if (hp <= 0)
		destroy = true;

	auto moveEvent = MoveBy::create(0.f, Vec2(0, -1) * 1);
	node->runAction(moveEvent);
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
		hp = 0;
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




