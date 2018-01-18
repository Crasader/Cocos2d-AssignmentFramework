#include "WaveManager.h"
#include "MasterManager.h"
using namespace cocos2d;

WaveManager::WaveManager()
{
	MASTERMANAGER_CALLBACK_INIT_FUNC(WaveManager, Init)
	MASTERMANAGER_CALLBACK_UPDATE_FUNC(WaveManager, Update)
}

WaveManager::~WaveManager()
{
}

void WaveManager::Init()
{
	Wave* temp = Wave::Create(RandomHelper::random_int(1, 8));//5);
	temp->Init();
	Wave_List.push_back(temp);

	
}

void WaveManager::Update(float dt)
{
	if (Wave_List.size() != 0)
	{
		Wave_List.front()->Update(dt);
		if (Wave_List.front()->finished)
		{
			Wave* temp = Wave_List.front();
			Wave_List.pop_front();
			delete temp;
		}			
	}
}

void WaveManager::Run_next_wave()
{
	if (Wave_List.size() == 0)
		return;
	Wave* temp = Wave_List.front();
	temp->Run();
}

void WaveManager::Add_wave(Wave* wave)
{
	Wave_List.push_back(wave);
}

void WaveManager::Add_wave(int index)
{
	switch (index)
	{
	case 0:
	{
		Wave* temp = Wave::Create(RandomHelper::random_int(1, 8));
		temp->Init();
		Wave_List.push_back(temp);
	}		
		break;
	default:
		break;
	}
	
}

Wave* WaveManager::get_current_wave()
{
	if (Wave_List.size() == 0)
		return NULL;
	return Wave_List.front();
}