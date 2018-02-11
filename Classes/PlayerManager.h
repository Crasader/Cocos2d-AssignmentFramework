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
	SINGLETON_CLASS(PlayerManager)
	virtual void Init();
	virtual void Update(float dt);
	void Add_Player(Player* player);
	void Remove_Player(Player* player);
	void Remove_All_Players();
	Player* get_Player(int index);
	Player* createPlayer();

	void OnTouchMove(Touch* touch, Event* event);


	vector<Player*> List_of_players;
private:
	PlayerManager();
	~PlayerManager();
};



#endif