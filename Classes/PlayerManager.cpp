#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
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
