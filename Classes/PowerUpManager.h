#ifndef POWERUP_MANAGER_H_
#define POWERUP_MANAGER_H_

#include "PowerUp.h"

class PowerUpManager
{
public:
	static PowerUpManager& getInstance()
	{
		static PowerUpManager Instance;
		return Instance;
	}
	PowerUpManager(const PowerUpManager&) = delete;
	PowerUpManager& operator=(const PowerUpManager&) = delete;
	

	void Init();
	void Update(float dt);
	void CreatePowerUp(string sprite_filename, PowerUp::TypesOfPowerUp types, Player* player, Vec2 position);

	void Release();
public:
	std::vector<PowerUp*>PowerUpList;
private:
	PowerUpManager();
	~PowerUpManager();
};



#endif