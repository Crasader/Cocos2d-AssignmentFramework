#include "PlayerManager.h"
#include "MasterManager.h"
PlayerManager::PlayerManager()
{
	//MASTERMANAGER_CALLBACK_INIT_FUNC(ProjectileManager, Init)
	//MASTERMANAGER_CALLBACK_UPDATE_FUNC(ProjectileManager, Update)
}

PlayerManager::~PlayerManager()
{
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
			delete *it;
			List_of_players.erase(it);
			break;
		}
	}
}

Player* PlayerManager::get_Player(int index)
{
	return List_of_players[index];
}
