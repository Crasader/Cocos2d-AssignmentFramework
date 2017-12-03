#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(string sprite_filename)
{
	node = Node::create();
	node->setName(Name);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create("Player/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	movement_spd = 10.0f;
}

void Player::Update(float delta)
{
	for (int i = 0; i < ProjectileList.size(); i++)
	{
		ProjectileList.at(i)->Update(delta);
		/*if (ProjectileList.at(i)->destroy)
		{
			BaseProjectile* temp = ProjectileList.at(i);
			delete temp;
			--i;
		}*/
	}
}

Node* Player::get_Node()
{
	return node;
}

Node* Player::get_spriteNode()
{
	return spriteNode;
}

void Player::set_Position(float x, float y)
{
	node->setPosition(x, y);
}

void Player::Move(Movement_Direction dir)
{
	switch (dir)
	{
	case Player::Up:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0, movement_spd));
		node->runAction(moveEvent);
	}		
		break;
	case Player::Down:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0, -movement_spd));
		node->runAction(moveEvent);
	}		
		break;
	case Player::Left:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(-movement_spd, 0));
		node->runAction(moveEvent);
	}		
		break;
	case Player::Right:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(movement_spd,0));
		node->runAction(moveEvent);
	}		
		break;
	default:
		break;
	}
}

void Player::Shoot()
{
	BaseProjectile* temp = BaseProjectile::create();
	temp->Init("projectile1.png", Vec2(0.f, 4.f),node->getPosition());
	ProjectileList.push_back(temp);
}

Player* Player::create(string name)
{
	Player* temp = new Player();
	temp->Set_Name(name);
	return temp;
}

void Player::Set_Name(string name)
{
	this->Name = name;
}
