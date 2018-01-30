#ifndef SHIELD_MANAGER_H_
#define SHIELD_MANAGER_H_

#include "Shield.h"
#include "GenericManager.h"

class ShieldManager : GenericManager
{
public:
	static ShieldManager& getInstance()
	{
		static ShieldManager Instance;
		return Instance;
	}

	void Init();
	void Update(float dt);
	void CreateShield(string sprite_filename, Player* player);

	std::vector<Shield*> ShieldList;

	void Release();

	ShieldManager(const ShieldManager&) = delete;
	ShieldManager& operator=(const ShieldManager&) = delete;
private:
	ShieldManager();
	~ShieldManager();



	//static ShieldManager* instance;
};



#endif