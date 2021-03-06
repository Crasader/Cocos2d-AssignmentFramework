#include "Player.h"
#include "EnemyManager.h"
#include "PowerUpManager.h"
#include "ShieldManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#ifdef __APPLE__
#include "InputManager/InputManager.h"
#else
#include "InputManager\InputManager.h"
#endif

#define SHOOTING_SPEED 0.3f
#define MAX_POWER 2
Player::Player() :
	dead(false),
	m_Max_Power(2)
{
}

Player::~Player()
{
	while (animFrames_tilt_left.size() > 0)
	{
		SpriteFrame* frame = animFrames_tilt_left.back();
		frame->release();
		animFrames_tilt_left.popBack();
		//delete frame;
	}
	while (animFrames_tilt_right.size() > 0)
	{
		SpriteFrame* frame = animFrames_tilt_right.back();
		frame->release();
		animFrames_tilt_right.popBack();
		//delete frame;
	}
	if (animFrames_idle.size() > 0)
	{
		SpriteFrame* frame = animFrames_idle.back();
		frame->release();
		animFrames_idle.popBack();
		//delete frame;
	}
	
}

void Player::Init(string sprite_filename)
{
	//animFrames_idle.clear();

	//PlayerManager::getInstance().Add_Player(this);
	node = Node::create();
	node->setName(Name);
	node->setAnchorPoint(Vec2(0.5f, 0.5f));
	spriteNode = Node::create();
	spriteNode->setName(Name + "_spriteNode");
	spriteNode->setAnchorPoint(Vec2(0.5f, 0.5f));
	node->addChild(spriteNode);
	SceneManager::getInstance().get_current_scene()->addChild(node);
	
	sprite = Sprite::create("Player/" + sprite_filename);
	sprite->setName(Name + "_sprite");
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//sprite->setContentSize(SceneManager::AdjustContentSize(sprite->getContentSize() , 0.065f));
	SceneManager::AdjustContentSize(sprite, 0.065f);
	spriteNode->addChild(sprite, 0);
	movement_spd = 10.0f;
	moving_state = Moving_State::Idle;
	{
		animFrames_tilt_left.reserve(4);
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_01.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_02.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_03.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_left.pushBack(SpriteFrame::create("Player/Plane_Left_04.png", Rect(0, 0, 64, 64)));

		/*for (int i = 0; i < animFrames_tilt_left.size(); ++i)
		{
			animFrames_tilt_left.at(i)->setOriginalSize(SceneManager::AdjustContentSize(animFrames_tilt_left.at(i)->getOriginalSize(),0.65f));
		}*/
	}
	{
		//Loading each frames
		animFrames_tilt_right.reserve(4);
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_01.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_02.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_03.png", Rect(0, 0, 64, 64)));
		animFrames_tilt_right.pushBack(SpriteFrame::create("Player/Plane_Right_04.png", Rect(0, 0, 64, 64)));
		/*for (int i = 0; i < animFrames_tilt_left.size(); ++i)
		{
			animFrames_tilt_right.at(i)->setOriginalSize(SceneManager::AdjustContentSize(animFrames_tilt_right.at(i)->getOriginalSize(), 0.65f));
		}*/
	}
	{
		animFrames_idle.reserve(1);
		animFrames_idle.pushBack(SpriteFrame::create("Player/Plane_Idle.png", Rect(0, 0, 64, 64)));
		//animFrames_idle.at(0)->setOriginalSize(SceneManager::AdjustContentSize(animFrames_idle.at(0)->getOriginalSize(), 0.65f));
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
	bulletMultiply = 1;
	PowerLevel = 0;
	shooting_timer = 0;
}

void Player::Update(float delta)
{
	Collision();
	string t = std::to_string(delta);//"HP: " + std::to_string(hp);
	//CCLOG(t.c_str());
	if (shooting_timer < SHOOTING_SPEED)
	{
		shooting_timer += delta;
	}

	if (InputManager::getInstance().isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_SPACE))
		Shoot();
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

void Player::Move_AnimationOnly(Movement_Direction dir)
{
	switch (dir)
	{
	case Player::Movement_Direction::Left:
	{
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

void Player::Move_PositionOnly(Vec2 dirVec)
{
	Vec2 temp = node->getPosition();
	temp += dirVec;
	node->setPosition(temp);
}

void Player::Shoot()
{
	if (shooting_timer >= SHOOTING_SPEED)
	{
		ProjectileManager::getInstance().CreateProjectile(PowerLevel);
		shooting_timer = 0;
	}
		
	return;
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
	if (hp <= 0)
		dead = true;
}

void Player::get_hit(int damage)
{
	hp -= damage;
	if (hp <= 0)
		dead = true;
}

void Player::Collision()
{
//#define ENEMYLIST EnemyManager::getInstance().EnemyList
#define POWERUPLIST PowerUpManager::getInstance().PowerUpList

	CCRect Player_rect = CCRectMake(
		node->getPosition().x - (sprite->getContentSize().width * 0.5f),
		node->getPosition().y - (sprite->getContentSize().height * 0.5f),
		sprite->getContentSize().width,
		sprite->getContentSize().height
	);

	//for (int i = 0; i < ENEMYLIST.size(); ++i)
	//{
	//	CCRect enemy_rect = CCRectMake(
	//		ENEMYLIST.at(i)->get_Node()->getPosition().x - (ENEMYLIST.at(i)->getSprite()->getContentSize().width * 0.5f),
	//		ENEMYLIST.at(i)->get_Node()->getPosition().y - (ENEMYLIST.at(i)->getSprite()->getContentSize().height * 0.5f),
	//		ENEMYLIST.at(i)->getSprite()->getContentSize().width,
	//		ENEMYLIST.at(i)->getSprite()->getContentSize().height
	//	);

	//	if (Player_rect.intersectsRect(enemy_rect))
	//	{
	//		//ENEMYLIST.at(i)->get_hit(damage);
	//		get_hit(ENEMYLIST.at(i)->get_damage());
	//		ENEMYLIST.at(i)->destroy = true;
	//		break;
	//	}
	//}
	for (int i = 0; i < POWERUPLIST.size(); ++i)
	{
		CCRect powerup_rect = CCRectMake(
			POWERUPLIST.at(i)->get_Node()->getPosition().x - (POWERUPLIST.at(i)->getSprite()->getContentSize().width * 0.5f),
			POWERUPLIST.at(i)->get_Node()->getPosition().y - (POWERUPLIST.at(i)->getSprite()->getContentSize().height * 0.5f),
			POWERUPLIST.at(i)->getSprite()->getContentSize().width,
			POWERUPLIST.at(i)->getSprite()->getContentSize().height
		);

		if (Player_rect.intersectsRect(powerup_rect))
		{
			/*POWERUPLIST.at(i)->destroy = true;

			switch (POWERUPLIST.at(i)->typeOfPowerUp)
			{
			
			case PowerUp::HEAL:
				set_hp(get_hp() + 5);
				break;
			case PowerUp::SHIELD:
				ShieldManager::getInstance().CreateShield("shield_activated.png", this);
				break;
			case PowerUp::MULTISHOT:
				bulletMultiply++;
				if (PowerLevel < MAX_POWER)
					++PowerLevel;
				break;

			default:
				break;
			}

			break;*/
		}
	}
}

void Player::Exit()
{
	SceneManager::getInstance().get_current_scene()->removeChild(node);
}

Player* Player::create(string name)
{
	Player* temp = new Player();
	temp->Set_Name(name);
	//PlayerManager::getInstance().Add_Player(temp);
	return temp;
}

void Player::Set_Name(string name)
{
	this->Name = name;
}

void Player::Release()
{
	/*while (animFrames_tilt_left.size() > 0)
	{

	}
	while (animFrames_tilt_left.size() > 0)
	{

	}
	animFrames_idle.clear();*/
}