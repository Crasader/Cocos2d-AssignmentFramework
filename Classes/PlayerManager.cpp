#include "PlayerManager.h"
#include "MasterManager.h"
#include "SceneManager.h"
#ifdef __APPLE__
#include "InputManager/InputManager.h"
#else
#include "InputManager\InputManager.h"
#endif

PlayerManager::PlayerManager()
{
	MASTERMANAGER_CALLBACK_INIT_FUNC(PlayerManager, Init)
	MASTERMANAGER_CALLBACK_UPDATE_FUNC(PlayerManager, Update)
	CCLOG("Player manager constructor");
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Init()
{
	if (List_of_players.size() != 0)
	{
		Player* temp = List_of_players[0];
		temp->Release();
		List_of_players.pop_back();
		delete temp;
	}

	InputManager::getInstance().m_onTouchMove_EventListMap.push_back([](Touch* touch, Event* event) {
		PlayerManager().getInstance().OnTouchMove(touch, event);
	});

	if (List_of_players.size() > 0)
	{
		Remove_All_Players();
	}

	createPlayer();
}

void PlayerManager::Update(float dt)
{
#ifdef __APPLE__

#else
	if (InputManager::getInstance().isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
		get_Player(0)->Move(Player::Movement_Direction::Right);
	if (InputManager::getInstance().isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		get_Player(0)->Move(Player::Movement_Direction::Left);

	if (InputManager::getInstance().isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW))
		get_Player(0)->Move(Player::Movement_Direction::Up);
	if (InputManager::getInstance().isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW))
		get_Player(0)->Move(Player::Movement_Direction::Down);


#endif
	



	for (vector<Player*>::iterator it = List_of_players.begin(); it < List_of_players.end(); it++)
	{
		(*it)->Update(dt);
	}

}

void PlayerManager::Add_Player(Player* player)
{
	List_of_players.push_back(player);
}

void PlayerManager::Remove_Player(Player* player)
{
	for (vector<Player*>::iterator it = List_of_players.begin(); it < List_of_players.end(); it++)
	{
		if (*it == player)
		{
			(*it)->Exit();
			delete *it;
			List_of_players.erase(it);
			break;
		}
	}
}

void PlayerManager::Remove_All_Players()
{
	while (List_of_players.size() > 0)
	{
		Player* temp = List_of_players.back();
		temp->Exit();
		delete temp;
		List_of_players.pop_back();
	}
}

Player* PlayerManager::get_Player(int index)
{
	return List_of_players[index];
}

Player* PlayerManager::createPlayer()
{
	int playerIndex = List_of_players.size() + 1;
	Player* temp = Player::create("Player" + std::to_string(playerIndex));
	temp->Init("Plane_Idle.png");
	Size playingsize = SceneManager::getInstance().currScene_playingSize;
	temp->set_Position(playingsize.width * 0.5f, playingsize.height * 0.5f);
	Add_Player(temp);
	return temp;
}

void PlayerManager::OnTouchMove(Touch* touch, Event* event)
{
	EventMouse* temp = (EventMouse*)event;
	Vec2 prevLocation = touch->getPreviousLocation();
	Vec2 currLocation = touch->getLocation();
	Vec2 dirvec = touch->getLocation() - touch->getPreviousLocation();
	get_Player(0)->Move_PositionOnly(dirvec);
	if (dirvec.x > 0.f)
	{
		get_Player(0)->Move_AnimationOnly(Player::Movement_Direction::Right);
	}
	else if (dirvec.x < 0.f)
	{
		get_Player(0)->Move_AnimationOnly(Player::Movement_Direction::Left);
	}
}