
#include "Enemy.h"


Enemy::Enemy()
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


}


void Enemy::Update(float dt)
{
	auto moveEvent = MoveBy::create(0.f, Vec2(0, -1) * 1);
	spriteNode->runAction(moveEvent);
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

Enemy* Enemy::create(string name)
{
	Enemy* temp = new Enemy();
	temp->Set_Name(name);
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






