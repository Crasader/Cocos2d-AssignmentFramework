#ifndef WAVE_MANAGER_H_
#define WAVE_MANAGER_H_
//#include <json\json\json.h>
#include <JSON\json\json.h>
#include "Wave.h"
#include "EnemyManager.h"


class WaveManager
{
public:
	static WaveManager& getInstance()
	{
		static WaveManager Instance;
		return Instance;
	}
	WaveManager(const WaveManager&) = delete;
	WaveManager& operator=(const WaveManager&) = delete;
	
	void Init();
	void Update(float dt);
	void Run_next_wave();
	void Add_wave(Wave* wave);
	void Add_wave(int index);
	Wave* get_current_wave();

	list<Wave*> Wave_List;
private:
	WaveManager();
	~WaveManager();
};

#endif