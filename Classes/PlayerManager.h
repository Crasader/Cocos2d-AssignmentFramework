#ifndef PLAYER_MANAGER_H_
#define PLAYER_MANAGER_H_
#include "cocos2d.h"
#include "Player.h"
#include "GenericManager.h"
using namespace cocos2d;
using namespace std;
class PlayerManager : GenericManager
{
public:
	static PlayerManager& getInstance()
	{
		static PlayerManager Instance;
		return Instance;
	}
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;
	PlayerManager();
	~PlayerManager();
	void Add_Player(Player* player);
	void Remove_Player(Player* player);
	Player* get_Player(int index);

	vector<Player*> List_of_players;

private:

};



#endif