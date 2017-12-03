#include "BaseProjectile.h"

BaseProjectile::BaseProjectile() : destroy(false), lifetime(3.f)
{
}

BaseProjectile::~BaseProjectile()
{
}

void BaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("BaseProjectile");
	node->addChild(sprite);
	movement_spd = 10.f;
	Direction_Vector = Direction_vector;
	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void BaseProjectile::Init(string sprite_filename, Vec2 Direction_vector, Vec2 position, float lifetime)
{
	node = Node::create();
	node->setPosition(position);
	sprite = Sprite::create("Projectile/" + sprite_filename);
	sprite->setName("BaseProjectile");
	node->addChild(sprite);
	movement_spd = 5.f;
	Direction_Vector = Direction_vector;
	this->lifetime = lifetime;
	CCDirector::getInstance()->getRunningScene()->addChild(node);
}

void BaseProjectile::Update(float delta)
{
	lifetime -= delta;
	if (lifetime <= 0 && !destroy)
		destroy = true;

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

BaseProjectile* BaseProjectile::create()
{
	return new BaseProjectile();
}

void BaseProjectile::release()
{
	CCDirector::getInstance()->getRunningScene()->removeChild(node);
	delete sprite;
	delete node;
}

void BaseProjectile::retain()
{

}