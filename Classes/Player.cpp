#include "Player.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
Player::Player() :
	dead(false)
{
}

Player::~Player()
{
}

void Player::Init(string sprite_filename)
{
	PlayerManager::getInstance().Add_Player(this);
	node = Node::create();
	node->setName(Name);
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	node->addChild(spriteNode);
	sprite = Sprite::create("Player/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	spriteNode->addChild(sprite, 0);
	movement_spd = 10.0f;
	moving_state = Moving_State::Idle;
	{
		animFrames_tilt_left.reserve(4);
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_01.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_02.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_03.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_04.png", Rect(0, 0, 64, 64)));
	}
	{
		//Loading each frames
		animFrames_tilt_right.reserve(4);
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_01.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_02.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_03.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_04.png", Rect(0, 0, 64, 64)));
		
	}
	{
		animFrames_idle.reserve(1);
		animFrames_idle.pushBack(SpriteFrame::create("Player/Plane_Idle.png", Rect(0, 0, 64, 64)));
	}
	original_sprite = SpriteFrame::create("Player/Plane_Idle.png", Rect(0, 0, 64, 64));
	//idle_anim = Animate::create(Animation::create()->addSpriteFrame(SpriteFrame::create("Player/Plane_Default.png", Rect(0, 0, 64, 64))));
	auto tempanimation = Animation::create();
	tempanimation->addSpriteFrame(SpriteFrame::create("Player/Plane_Idle.png", Rect(0, 0, 64, 64)));
	idle_anim = Animate::create(tempanimation);
	sprite->runAction(RepeatForever::create(idle_anim));
	

	//tilt_left = Add_animation("plane_left_spritesheet.plist", "plane_left");
	//tilt_right = Add_animation("plane_right_spritesheet.plist", "plane_right");

	hp = 100;

}

void Player::Update(float delta)
{
	Collision();
	string t = "HP: " + std::to_string(hp);
	CCLOG(t.c_str());

	if (hp <= 0)
		dead = true;
	//for (int i = 0; i < ProjectileList.size(); i++)
	//{
	//	ProjectileList.at(i)->Update(delta);
	//	/*if (ProjectileList.at(i)->destroy)
	//	{
	//		BaseProjectile* temp = ProjectileList.at(i);
	//		delete temp;
	//		--i;
	//	}*/
	//}
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

Animate* Player::Add_animation(string plist_filename, string animation__name)
{
	auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile("Player/" + plist_filename);
	auto animation = cache->animationByName(animation__name);
	return Animate::create(animation);
}

void Player::Move(Movement_Direction dir)
{
	switch (dir)
	{
	case Player::Movement_Direction::Up:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0, movement_spd));
		node->runAction(moveEvent);
	}		
		break;
	case Player::Movement_Direction::Down:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0, -movement_spd));
		node->runAction(moveEvent);
	}		
		break;
	case Player::Movement_Direction::Left:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(-movement_spd, 0));
		node->runAction(moveEvent);
		if (moving_state == Moving_State::Idle)
		{
			moving_state = Moving_State::Tilting_Left;
			Animation* animation = Animation::createWithSpriteFrames(animFrames_tilt_left, 0.1f);
			Animate* tilt_left = Animate::create(animation);
			sprite->runAction(tilt_left);
		}		
	}		
		break;
	case Player::Movement_Direction::Right:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(movement_spd,0));
		node->runAction(moveEvent);
		if (moving_state == Moving_State::Idle)
		{
			moving_state = Moving_State::Tilting_Right;
			Animation* animation = Animation::createWithSpriteFrames(animFrames_tilt_right, 0.1f);
			Animate* tilt_right = Animate::create(animation);
			sprite->runAction(tilt_right);
		}
	}		
		break;
	default:
		break;
	}
}

void Player::Shoot()
{
	/*BaseProjectile* temp = BaseProjectile::create();
	temp->Init("projectile1.png", Vec2(0.f, 4.f),node->getPosition());
	ProjectileList.push_back(temp);*/
	//ProjectileManager::getInstance().CreateProjectile("projectile1.png", Vec2(0.f, 4.f), node->getPosition());
	ProjectileManager::getInstance().CreateProjectile(0);
}

void Player::Set_moving_state(Moving_State mov_st)
{
	moving_state = mov_st;
	sprite->stopAllActions();
	/*Animation* animation = Animation::createWithSpriteFrames(animFrames_idle, 0.1f);
	Animate* tempidle = Animate::create(animation);
	sprite->runAction(RepeatForever::create(tempidle));*/
	sprite->setSpriteFrame(SpriteFrame::create("Player/Plane_Idle.png", Rect(0, 0, 64, 64)));
}

int Player::get_hp()
{
	return hp;
}

void Player::set_hp(int hp)
{
	this->hp = hp;
}

void Player::get_hit(int damage)
{
	hp -= damage;
}

void Player::Collision()
{
#define ENEMYLIST EnemyManager::getInstance().EnemyList

	CCRect Player_rect = CCRectMake(
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

		if (Player_rect.intersectsRect(enemy_rect))
		{
			//ENEMYLIST.at(i)->get_hit(damage);
			get_hit(ENEMYLIST.at(i)->get_damage());
			ENEMYLIST.at(i)->destroy = true;
			break;
		}
	}
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
