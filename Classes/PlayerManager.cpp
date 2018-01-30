#include "PlayerManager.h"
#include "MasterManager.h"
#include "SceneManager.h"
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
	if (List_of_players.size() > 0)
	{
		Remove_All_Players();
	}

	createPlayer();
}

void PlayerManager::Update(float dt)
{
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
	//this->addChild(player1->get_Node(), 1);
	//SceneManager::getInstance().get_current_scene()->addChild();
	Size playingsize = SceneManager::getInstance().currScene_playingSize;
	temp->set_Position(playingsize.width * 0.5f, playingsize.height * 0.5f);
	Add_Player(temp);
	return temp;
}